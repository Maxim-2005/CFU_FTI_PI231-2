package main

import "fmt"

func main() {
  var n, x, k, t, a, b int
  var arr []int
  var p bool

  a, b = 0, 0
  fmt.Scan(&n, &x)
  for i := 0; i < n; i++ {
    fmt.Scan(&k)
    if k < x {
      p = true
      t = x - k
      for _, j := range arr {
        if j == t {
          if k > j {
            a, b = j, k
          } else {
            a, b = k, j
          }
          break
        } else if j == k {
          p = false
        }
      }
      if p {
        arr = append(arr, k)
      }
    }
  }

  fmt.Println(a, b)
}