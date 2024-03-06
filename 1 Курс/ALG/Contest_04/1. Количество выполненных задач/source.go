package main

import (
	"encoding/json"
	"fmt"
	"io"
	"log"
	"os"
)

// структура задачи
type Task struct {
	User_id   int
	Id        int
	Title     string
	Completed bool
}

// структура проекта
type Project struct {
	Project_id int
	Tasks      []Task
}

func main() {
	var (
		projects []Project // полученные данные
		n, s     int       // идентификатор пользователя, кол-во решенных задач
	)

	fmt.Scan(&n)

	// открытие файла
	file, err := os.Open("data.json")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	// чтение файла
	data, err := io.ReadAll(file)
	if err != nil {
		log.Fatal(err)
	}

	// преобразование данных в структуры
	jsonErr := json.Unmarshal(data, &projects)
	if jsonErr != nil {
		log.Fatal(jsonErr)
	}

	// обход всех заданий во всех проектах
	for _, project := range projects {
		for _, task := range project.Tasks {
			if task.User_id == n && task.Completed {
				s++
			}
		}
	}

	fmt.Println(s)
}
