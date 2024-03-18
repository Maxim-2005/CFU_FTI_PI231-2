func shift(data []int, steps int) { // массив чисел, колличество сдвигов
	temp := make([]int, len(data), cap(data))        // временный массив
	n := (len(data)*2 - steps%len(data)) % len(data) // сдвиг
	temp = append(data[n:], data[:n]...)             // добавление в конец
	copy(data, temp)                                 // копирование
}