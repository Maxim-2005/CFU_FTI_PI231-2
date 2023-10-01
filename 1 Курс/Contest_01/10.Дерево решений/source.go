package main
import "fmt"

func main() {
    
    var a, b, c string
    
    fmt.Scan(&a, &b, &c)
    
    if a == "Нет"{
        if b == "Нет"{
            if c == "Нет"{
                fmt.Print("Кот")
            }else if c == "Да"{
                fmt.Print("Жираф")
            }
        }else if b == "Да"{
            if c == "Нет"{
                fmt.Print("Курица")
            }else if c == "Да"{
                fmt.Print("Страус")
            }
        }
    }else if a == "Да"{
        if b == "Нет"{
            if c == "Нет"{
                fmt.Print("Дельфин")
            }else if c == "Да"{
                fmt.Print("Плезиозавры")
            }
        }else if b == "Да"{
            if c == "Нет"{
                fmt.Print("Пингвин")
            }else if c == "Да"{
                fmt.Print("Утка")
            }
        }
    }
}