package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)

type Passager struct {
	name string
	age  int
}

func main() {
	var (
		line   []string   // строка файла
		t      []string   // строка списка
		v      []Passager // список пассажиров
		p      Passager   // временный пассажир
		s      string     // скейка имени
		n      string     // имя пассажира
		pclass int        // необходимый класс пассажира
		age    int        // минимальный возраст пассажира
		a      int        // возраст пассажира
		c      int        // класс пассажира
	)

	fmt.Scan(&pclass, &age)

	// открывем файл csv
	file, err := os.Open("train.csv")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	// сканируем большой текст с разбивкой по строкам
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line = strings.Split(scanner.Text(), "\r")
		for _, w := range line {
			t = strings.Split(w, ",")
			a, err = strconv.Atoi(t[6])
			c, err = strconv.Atoi(t[2])
			if t[5] == "female" && a > age && c == pclass {
				s = t[3] + "," + t[4] // склеиваем имя, восстанавливаем ","
				// убраем лишние кавычки
				n = ""
				for i := 1; i < len(s)-1; i++ {
					if !(s[i-1] == '"' && s[i] == '"') {
						n += string(s[i])
					}
				}
				p = Passager{name: n, age: a}
				v = append(v, p)
			}
		}
	}

	// сортировка с условиями (вручную)
	for i := 0; i < len(v); i++ {
		for j := i + 1; j < len(v); j++ {
			if v[i].age > v[j].age || (v[i].age == v[j].age && v[i].name > v[j].name) {
				p = v[i]
				v[i] = v[j]
				v[j] = p
			}
		}
	}

	// вывод списка
	for _, i := range v {
		fmt.Println(i.name)
	}
}
