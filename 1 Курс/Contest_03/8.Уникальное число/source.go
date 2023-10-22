package main

import "fmt"

func main() {
    var n int
    fmt.Scan(&n)
    
    nums := make(map[int]int)
    
    for i := 0; i < n; i++ {
        var num int
        fmt.Scan(&num)
        
        nums[num]++
    }
    
    for num, count := range nums {
        if  ((count % 2 ) == 1) {
            fmt.Println(num)
            break
        }
    }
}