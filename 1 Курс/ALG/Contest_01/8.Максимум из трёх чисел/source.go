package main

import "fmt"

func main() {

	var a, b, c int // проверяемые числа

	fmt.Scan(&a, &b, &c)

	// вычисление наибольшего из 3 чисел
	if a > b && a > c {
		fmt.Print(a)
	} else if b > a && b > c {
		fmt.Print(b)
	} else {
		fmt.Print(c)
	}
}
