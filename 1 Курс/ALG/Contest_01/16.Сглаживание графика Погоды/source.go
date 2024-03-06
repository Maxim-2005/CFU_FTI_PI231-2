package main

import "fmt"

func main() {
	var n int // длина последовательности
	fmt.Scanln(&n)

	arr := make([]int, n) // результаты измерений
	for i := 0; i < n; i++ {
		fmt.Scan(&arr[i])
	}

	s := make([]float64, n) // cглаженная последовательность
	s[0] = float64(arr[0])

	for i := 1; i < n-1; i++ {
		s[i] = (float64(arr[i-1]) + float64(arr[i]) + float64(arr[i+1])) / 3.0
	}

	s[n-1] = float64(arr[n-1])

	for i := 0; i < n; i++ {
		fmt.Printf("%.10f ", s[i])
	}
	fmt.Println()
}
