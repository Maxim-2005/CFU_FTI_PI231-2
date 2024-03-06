import (
	"strings"
)

func isPalindrome(s string) bool {
	s = strings.ToLower(s)
	left := 0
	right := len(s) - 1

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

func check(c byte) bool {
	return (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')
}