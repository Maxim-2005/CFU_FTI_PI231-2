package main
// Подключение библиотек
import "math"
import "fmt"

// Объявление переменных
var c, d, t float64

func main() {

    // Всего литров воздуха за год
    c = 0.5 * 365
    // Сколько нужно дубов
    d = c / 20
    // Сколько нужно тополей
    t = c / 32

    // Вывод ответа
    fmt.Print(c, math.Ceil(t), math.Ceil(d))
}
