package main

import "fmt"

////////////////////////////// ДЛЯ ТЕСТА

type Queue []int

func (self *Queue) Push(x int) {
	*self = append(*self, x)
}

func (self *Queue) IsEmpty() bool {
	return len(*self) == 0
}

func (self *Queue) Pop() int {
	h := *self
	var el int
	l := len(h)
	el, *self = h[0], h[1:l]
	return el
}

func NewQueue() *Queue {
	return &Queue{}
}

//////////////////////////////

type Water struct {
	temperature int
}

func NewWater(temperature int) *Water {
	return &Water{
		temperature: temperature,
	}
}

type Teapot struct {
	water *Water
}

func NewTeapot(water *Water) *Teapot {
	return &Teapot{
		water: water,
	}
}

func (this *Teapot) is_boiling() bool {
	return this.water.temperature >= 100
}

func (this *Teapot) heat_up(t int) {
	this.water.temperature += t
}

func main() {
	var temperature, count int
	fmt.Scan(&temperature, &count)

	heat := NewQueue()
	for i := 0; i < count; i++ {
		var t int
		fmt.Scan(&t)
		heat.Push(t)
	}

	water := NewWater(temperature)
	teapot := NewTeapot(water)

	for !teapot.is_boiling() {
		teapot.heat_up(heat.Pop())
	}

	for !heat.IsEmpty() {
		fmt.Print(heat.Pop(), " ")
	}
}
