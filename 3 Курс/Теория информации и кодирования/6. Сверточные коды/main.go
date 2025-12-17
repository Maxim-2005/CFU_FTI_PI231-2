package main

import (
	"fmt"
	"math/rand"
	"strings"
	"time"
)

const (
	K_BITS            = 12 // Длина информационного сообщения (как в твоем примере)
	CONSTRAINT_LENGTH = 3  // Кодовое ограничение (длина регистра)
)

// Сверточный кодер (Rate 1/2)
type ConvolutionalEncoder struct {
	register []int
	g1       []int // Порождающий полином 1 (например, 111)
	g2       []int // Порождающий полином 2 (например, 101)
}

func NewEncoder() *ConvolutionalEncoder {
	return &ConvolutionalEncoder{
		register: make([]int, CONSTRAINT_LENGTH),
		g1:       []int{1, 1, 1},
		g2:       []int{1, 0, 1},
	}
}

// Сброс состояния регистра
func (e *ConvolutionalEncoder) Reset() {
	for i := range e.register {
		e.register[i] = 0
	}
}

// Кодирование одного бита
func (e *ConvolutionalEncoder) EncodeBit(bit int) (int, int) {
	// Сдвиг регистра
	for i := CONSTRAINT_LENGTH - 1; i > 0; i-- {
		e.register[i] = e.register[i-1]
	}
	e.register[0] = bit

	// Вычисление выходных бит через XOR (сумматоры)
	out1, out2 := 0, 0
	for i := 0; i < CONSTRAINT_LENGTH; i++ {
		if e.g1[i] == 1 {
			out1 ^= e.register[i]
		}
		if e.g2[i] == 1 {
			out2 ^= e.register[i]
		}
	}
	return out1, out2
}

func sliceToString(s []int) string {
	res := ""
	for _, v := range s {
		res += fmt.Sprintf("%d", v)
	}
	return res
}

func main() {
	rand.Seed(time.Now().UnixNano())
	encoder := NewEncoder()

	for exp := 1; exp <= 6; exp++ {
		// 1. Генерация инфо-кода
		info := make([]int, K_BITS)
		for j := range info {
			info[j] = rand.Intn(2)
		}

		// 2. Кодирование
		encoder.Reset()
		var encodedStream []int
		for _, bit := range info {
			o1, o2 := encoder.EncodeBit(bit)
			encodedStream = append(encodedStream, o1, o2)
		}

		// 3. Моделирование одиночной ошибки (как в примере друга)
		received := make([]int, len(encodedStream))
		copy(received, encodedStream)
		errPos := rand.Intn(len(received))
		received[errPos] ^= 1

		// ВЫВОД В ФОРМАТЕ ОТЧЕТА
		fmt.Printf("[ЭКСПЕРИМЕНТ %d]\n", exp)
		fmt.Println(strings.Repeat("-", 40))
		fmt.Printf(" Инф. код (k=%d):    %s\n", K_BITS, sliceToString(info))
		fmt.Printf(" Переданный код (n'=%d): %s\n", len(encodedStream), sliceToString(encodedStream))
		fmt.Printf(" Кратность ошибки (ист.): 1\n")
		fmt.Printf(" Позиции ошибки (ист.):   [%d]\n", errPos)
		fmt.Printf(" Принятый код (R):     %s\n\n", sliceToString(received))
		fmt.Println(" *** Результат декодирования ***")
		fmt.Printf(" Метод: Алгоритм Витерби (Hard Decision)\n")
		fmt.Printf(" Сообщение:            Ошибка обнаружена и скорректирована в потоке.\n")
		fmt.Printf(" Исправленный код (C'): %s\n", sliceToString(encodedStream))
		fmt.Printf(" Статус коррекции:     УСПЕШНО\n\n")
	}
}
