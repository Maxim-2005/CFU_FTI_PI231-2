package main

import "fmt"

func main() {
	var row, col int // столбцы, колонки
	fmt.Scan(&row, &col)
	fmt.Printf("% 5v", "|")
	// вывод колличества колонок
	for i := 1; i <= col; i++ {
		fmt.Printf("% 4v", i)
	}
	fmt.Println()
	fmt.Printf("% 5v", "--")

	// выовод колонок
	for i := 1; i <= col; i++ {
		fmt.Printf("% 4v", "----")
	}
	fmt.Println()

	//вывод строк
	for i := 1; i <= row; i++ {
		fmt.Printf("% 4v|", i)
		for j := 1; j <= col; j++ {
			fmt.Printf("% 4v", i*j)
		}
		fmt.Println()
	}
}
