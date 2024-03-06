package main

import (
	"fmt"
	"math/rand"
)

// структура кота
type Cat struct {
	Live bool // жизнь и смерть кота
	Show bool // закрты или открыт кот
}

// Конструктор кота
func NewCat() Cat {
	cat := Cat{}
	cat.Live = rand.Intn(2) == 1
	cat.Show = false
	return cat
}

// демонстрируем состояние кота
func (c *Cat) is_alive() bool {
	if c.Show {
		return c.Live
	} else {
		c.Live = rand.Intn(2) == 1
		return c.Live
	}
}

// структура коробки
type Box struct{}

// функция открывания коробки
func (b *Box) open() Cat {
	cat := NewCat()
	cat.Show = true
	return cat
}

func main() {
	var box Box
	cat := box.open()
	if cat.is_alive() {
		fmt.Print("alive")
	} else {
		fmt.Print("dead")
	}
}
