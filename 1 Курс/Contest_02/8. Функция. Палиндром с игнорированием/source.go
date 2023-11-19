import (
	"strings"
)

func isPalindrome(s string) bool {
	s = strings.ToLower(s) // делаем все буквы маленькими
	left := 0              // начало слова
	right := len(s) - 1    // конец слова

	for left < right {
		if !check(s[left]) {
			left++
		} else if !check(s[right]) {
			right--
		} else if s[left] != s[right] {
			return false
		} else {
			left++
			right--
		}
	}

	return true
}

// проверка
func check(c byte) bool {
	return (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')
}