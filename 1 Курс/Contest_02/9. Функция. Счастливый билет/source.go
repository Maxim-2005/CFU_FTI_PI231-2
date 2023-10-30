import (
	"strconv"
)

func isLucky(s string) bool {

	sumLeft := 0  // сумма первых 3
	sumRight := 0 // сумма 2 трех

	// обход первых 3 знавчений и преобразование их в инт
	for i := 0; i < 3; i++ {
		num, err := strconv.Atoi(string(s[i]))
		if err != nil {
			return false
		}
		sumLeft += num
	}

	// обход вторыъ 3 знавчений и преобразование их в инт
	for i := 3; i < 6; i++ {
		num, err := strconv.Atoi(string(s[i]))
		if err != nil {
			return false
		}
		sumRight += num
	}
	return (sumLeft == sumRight)
}