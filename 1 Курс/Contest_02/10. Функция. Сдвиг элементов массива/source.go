func shift(data []int, steps int) {
	temp := make([]int, len(data), cap(data))
	n := (len(data)*2 - steps%len(data)) % len(data)
	temp = append(data[n:], data[:n]...)
	copy(data, temp)
}