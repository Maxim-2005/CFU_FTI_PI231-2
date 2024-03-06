package main

import (
	"fmt"
)

const rows int = 9
const cols int = 9

func test(arr []int) bool {
	for i := 0; i < len(arr); i++ {
		//for j := i; j < len(arr)-1; j++ {
		//var temp int
		//if arr[j] > arr[j+1] {
		//temp = arr[j]
		//arr[j] = arr[i+1]
		//arr[j+1] = temp
		//}
		//}
		arr[i] = 5
	}
	fmt.Print(arr)
	return true
}

func isValidSudoku(bord [rows][cols]int) bool {
	for i := 0; i < rows; i++ {
		test(bord[i])
	}
	return true
}

func main() {
	var bord [rows][cols]int

	for row := 0; row < rows; row++ {
		for col := 0; col < cols; col++ {
			fmt.Scanf("%c", &bord[row][col]) // Считываем один символ
			bord[row][col] -= '0'            // Чтобы из ASCII кода символа получить цифру
		}
		fmt.Scanf("\n")
	}

	if isValidSudoku(bord) {
		fmt.Println("YES")
	} else {
		fmt.Println("NO")
	}
}
