package main
// Импорт библиотеки
import "fmt"

func main() {

    // Объявление переменных
    var a, b int

    // Получение значения переменных с консоли
    fmt.Scan(&a)
    fmt.Scan(&b)

    // Вывод умножения
    fmt.Print(a * b)
}
