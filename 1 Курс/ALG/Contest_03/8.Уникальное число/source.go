package main

import "fmt"

func main() {
	var n int // большое количество целых чисел
	fmt.Scan(&n)

	nums := make(map[int]int) // словарь с колличеством повторений

	// запись чисел
	for i := 0; i < n; i++ {
		var num int
		fmt.Scan(&num)

		nums[num]++
	}

	// вывод ответа
	for num, count := range nums {
		if (count % 2) == 1 {
			fmt.Println(num)
			break
		}
	}
}
