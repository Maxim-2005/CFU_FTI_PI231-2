package main
import "math"
import "fmt"

var c, d, t float64

func main() {
    
    c = 0.5 * 365
    d = c / 20
    t = c / 32
    
    fmt.Print(c, math.Ceil(t), math.Ceil(d))
}