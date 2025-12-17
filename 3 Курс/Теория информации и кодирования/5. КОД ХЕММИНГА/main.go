package main

import (
	"fmt"
	"math/rand"
	"strings"
	"time"
)

// Твой параметр k по варианту
const K = 4

// Вспомогательная функция для печати слайса в строку
func sliceToString(s []int) string {
	res := ""
	for _, v := range s {
		res += fmt.Sprintf("%d", v)
	}
	return res
}

// Деление полиномов в GF(2) для получения остатка
func getRemainder(dividend, divisor []int) []int {
	// Исправлено: создаем слайс нужной длины типа []int
	res := make([]int, len(dividend))
	copy(res, dividend)

	for i := 0; i <= len(res)-len(divisor); i++ {
		if res[i] == 1 {
			for j := 0; j < len(divisor); j++ {
				res[i+j] ^= divisor[j]
			}
		}
	}
	// Возвращаем последние p разрядов
	return res[len(res)-(len(divisor)-1):]
}

func copySlice(s []int) []int {
	res := make([]int, len(s))
	copy(res, s)
	return res
}

// Расчет бита общей четности
func calculateOverallParity(data []int) int {
	p := 0
	for _, v := range data {
		p ^= v
	}
	return p
}

func main() {
	rand.Seed(time.Now().UnixNano())

	// Образующий полином для k=4: x^3 + x + 1
	genPol := []int{1, 0, 1, 1}
	pCount := len(genPol) - 1
	nPrime := K + pCount + 1 // n + 1 (общая четность)

	// Построение таблицы синдромов
	syndromeTable := make(map[string]int)
	for i := 0; i < K+pCount; i++ {
		v := make([]int, K+pCount)
		v[i] = 1
		rem := getRemainder(v, genPol)
		syndromeTable[sliceToString(rem)] = i
	}

	for i := 1; i <= 6; i++ {
		// а) Генерация инфо-кода
		info := make([]int, K)
		for j := range info {
			info[j] = rand.Intn(2)
		}

		// б) Кодирование
		cyclicPart := make([]int, K+pCount)
		copy(cyclicPart, info)
		rem := getRemainder(cyclicPart, genPol)
		for j := 0; j < pCount; j++ {
			cyclicPart[K+j] = rem[j]
		}

		// Добавление общей четности (P) в начало
		overallP := calculateOverallParity(cyclicPart)
		finalEncoded := append([]int{overallP}, cyclicPart...)

		// г) Внесение ошибки (1 или 2 для демонстрации)
		errCount := 1
		if i == 3 || i == 5 || i == 6 {
			errCount = 2
		} // Тестируем двойные ошибки

		received := copySlice(finalEncoded)
		var errPositions []int
		posUsed := make(map[int]bool)
		for len(errPositions) < errCount {
			p := rand.Intn(len(received))
			if !posUsed[p] {
				posUsed[p] = true
				errPositions = append(errPositions, p)
				received[p] ^= 1
			}
		}

		// --- ДЕКОДИРОВАНИЕ ---
		recP := received[0]
		recData := received[1:]
		calcP := calculateOverallParity(recData)
		syndrome := getRemainder(recData, genPol)

		isSynZero := true
		synVal := 0
		for _, v := range syndrome {
			synVal = (synVal << 1) | v
			if v != 0 {
				isSynZero = false
			}
		}

		pDiff := recP ^ calcP
		var msg, status string
		corrected := copySlice(received)
		detectedCount := errCount

		if isSynZero && pDiff == 0 {
			msg = "Ошибок не обнаружено."
			status = "УСПЕШНО"
			detectedCount = 0
		} else if !isSynZero && pDiff != 0 {
			posInTable, ok := syndromeTable[sliceToString(syndrome)]
			if ok {
				corrected[posInTable+1] ^= 1
				msg = fmt.Sprintf("Обнаружена и исправлена однократная ошибка в позиции %d.", posInTable+1)
				status = "УСПЕШНО"
				detectedCount = 1
			}
		} else if !isSynZero && pDiff == 0 {
			msg = "Обнаружена двукратная ошибка. Исправление невозможно."
			status = "НЕ ТРЕБУЕТСЯ / НЕВОЗМОЖНО"
			detectedCount = 2
		} else {
			msg = "Ошибка в проверочном бите четности."
			status = "УСПЕШНО"
			corrected[0] ^= 1
			detectedCount = 1
		}

		// ВЫВОД В ФОРМАТЕ ОДНОКУРСНИКА
		fmt.Printf("[ЭКСПЕРИМЕНТ %d]\n", i)
		fmt.Println(strings.Repeat("-", 40))
		fmt.Printf(" Инф. код (k=%d):    %s\n", K, sliceToString(info))
		fmt.Printf(" Переданный код (n'=%d): %s\n", nPrime, sliceToString(finalEncoded))
		fmt.Printf(" Кратность ошибки (ист.): %d\n", errCount)
		fmt.Printf(" Позиции ошибки (ист.):   %v\n", errPositions)
		fmt.Printf(" Принятый код (R):     %s\n\n", sliceToString(received))
		fmt.Println(" *** Результат декодирования ***")
		fmt.Printf(" Синдром S (dec/bin): %d/%s\n", synVal, sliceToString(syndrome))
		fmt.Printf(" Общая четность P:    %d\n", pDiff)
		fmt.Printf(" Обнаруж. кратность:  %d\n", detectedCount)
		fmt.Printf(" Сообщение:            %s\n", msg)
		fmt.Printf(" Исправленный код (C'): %s\n", sliceToString(corrected))
		fmt.Printf(" Статус коррекции:     %s\n\n", status)
	}
}
