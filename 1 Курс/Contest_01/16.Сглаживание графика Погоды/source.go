package main

import "fmt"

func smoothSequence(n int, sequence []int) []float64 {
 smoothed := make([]float64, n)
 smoothed[0] = float64(sequence[0])

 for i := 1; i < n-1; i++ {
  smoothed[i] = (float64(sequence[i-1]) + float64(sequence[i]) + float64(sequence[i+1])) / 3.0
 }

 smoothed[n-1] = float64(sequence[n-1])

 return smoothed
}

func main() {
 var n int
 fmt.Scanln(&n)

 sequence := make([]int, n)
 for i := 0; i < n; i++ {
  fmt.Scan(&sequence[i])
 }

 smoothed := smoothSequence(n, sequence)

 for i := 0; i < n; i++ {
  fmt.Printf("%.10f ", smoothed[i])
 }
 fmt.Println()
}