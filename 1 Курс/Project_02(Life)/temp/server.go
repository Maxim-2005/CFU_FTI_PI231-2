package main

import (
	"encoding/json"
	"fmt"
	"log"
	"net/http"
)

type Point struct {
	X int
	Y int
}

var matrix []Point

func main() {
	http.HandleFunc("/step", step)
	http.HandleFunc("/status", status)

	log.Println("Серевер работает на порту 8080")
	err := http.ListenAndServe("localhost:8080", nil)
	if err != nil {
		log.Fatal(err)
	}
}

// Вызов функции при GET и POST запросах
func step(w http.ResponseWriter, r *http.Request) {
	switch r.Method {
	case http.MethodGet:
		getPoint(w, r)
	case http.MethodPost:
		postPoint(w, r)
	default:
		http.Error(w, "Неизвестный запрос (используйте get или post)", http.StatusMethodNotAllowed)
	}
}

// Расчет следующего шага
func getPoint(w http.ResponseWriter, r *http.Request) {
	//json.NewEncoder(w).Encode(matrix)
	json.NewEncoder(w).Encode("Hello")
	fmt.Fprintf(w, "Следующий шаг: '%v'", matrix)
}

// Установка точки вручную
func postPoint(w http.ResponseWriter, r *http.Request) {
	var point Point
	err := json.NewDecoder(r.Body).Decode(&matrix)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}

	matrix = append(matrix, point)
	fmt.Fprintf(w, "Добавить точку: '%v'", matrix)
}

// Статус работы сервера
func status(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "Сервер работает")
}
