import (
    "strconv"
)

func isLucky(s string) bool{
    
    sumLeft := 0
    sumRight := 0
    
    for i := 0; i < 3; i++ {
        num, err := strconv.Atoi(string(s[i]))
        if err != nil {
            return false
        }
        sumLeft += num
    }

    for i := 3; i < 6; i++ {
        num, err := strconv.Atoi(string(s[i]))
        if err != nil {
            return false
        }
        sumRight += num
    }
    return (sumLeft == sumRight)
}