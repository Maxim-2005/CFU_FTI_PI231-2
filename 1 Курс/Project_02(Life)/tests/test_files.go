/**
 * Клеточный автомат
 * Студенты:
 * - Максим Покидько
 * - Усейной Даниэль
 * - Ярослав Епишенко
 * 10 января 2024 г.
 */

package main

import (
	"fmt"
	"os"
)

var correctly, errors int
var files = map[string]int64{
	"BackEnd/go.mod":         24,
	"BackEnd/server.go":      1358,
	"FrontEnd/css/style.css": 535,
	"FrontEnd/img/life.png":  17934,
	"FrontEnd/js/script.js":  12681,
	"FrontEnd/index.html":    914,
	"start.bat":              348,
}

func main() {
	for path, size := range files {
		correctly++
		file, err := os.Open(path)
		if err != nil {
			fmt.Println("Ошибка открытия: ", path)
			panic(err)
			errors++
		} else {
			fmt.Println("Файл в наличии: ", path)
		}

		info, err := file.Stat()
		if err != nil {
			fmt.Println("Ошибка свойств: ", path)
			panic(err)
			errors++
		} else {
			fmt.Println("Свойства доступны: ", path)
		}

		if size != info.Size() {
			fmt.Println("Неверный размер: ", size)
			errors++
		} else {
			fmt.Println("Размер проверен: ", size)
		}
	}
	fmt.Println("Всего файлов проверенно: ", correctly)
	fmt.Println("Колличество ошибок: ", errors)
}
