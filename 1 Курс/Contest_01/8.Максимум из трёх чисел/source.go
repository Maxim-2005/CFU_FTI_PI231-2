package main
import "fmt"

func main() {
    
    var a, b, c int
    
    fmt.Scan(&a, &b, &c)
    
    if a > b && a > c{
        fmt.Print(a)
    }else if b > a && b > c{
        fmt.Print(b)
    } else{
        fmt.Print(c)
    }
}