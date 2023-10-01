/******************************************************************************

                            Online Go Lang Compiler.
                Code, Compile, Run and Debug Go Lang program online.
Write your code in this editor and press "Run" button to execute it.

*******************************************************************************/


package main
import "fmt"

func main() {
    var (
        N int
        k5000 int = 0
        k1000 int = 0
        k500 int = 0
        k200 int = 0
        k100 int = 0
    )
    
    fmt.Scan(&N)
    
    for ; N / 5000 > 0; {
        N = N - 5000
        k5000++
    }
    for ; N / 1000 > 0; {
        N = N - 1000
        k1000++
    }
    for ; N / 500 > 0; {
        N = N - 500
        k500++
    }
    for ; N / 200 > 0; {
        N = N - 200
        k200++
    }
    for ; N / 100 > 0; {
        N = N - 100
        k100++
    }
    
    fmt.Print(k5000, k1000, k500, k200, k100)
}
