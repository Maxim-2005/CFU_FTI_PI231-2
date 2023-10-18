package main

import "fmt"

func main() {
	var n, x, k, t, a, b int // кол-во чисел, требуемая сумма, число, временная переменная для проверки, переменные для вывода ответа
	var arr []int // массив чисел
	var p bool // флаг для проверки необходимости добавляения числа в массив

	a, b = 0, 0
	fmt.Scan(&n, &x)
	// цикл принимающий все значения
	for i := 0; i < n; i++ {
		fmt.Scan(&k)
		// проверка числа относительно х
		if k < x {
			p = true
			t = x - k
			// Обход массива и нахождение пар
			for _, j := range arr {
				if j == t {
					if k > j {
						a, b = j, k
					} else {
						a, b = k, j
					}
					break
				} else if j == k {
					p = false
				}
			}
			if p {
				arr = append(arr, k)
			}
		}
	}

	fmt.Println(a, b)
}
