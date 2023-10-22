package main

import "fmt"

func main() {

	var a, t int // проверяемое число, счетчик

	fmt.Scan(&a)

	for a > 1 {
		if a%2 == 0 {
			a = a / 2
		} else {
			a = 3*a + 1
		}
		t++
	}
	fmt.Print(t)
}
