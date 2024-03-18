/**
 * Клеточный автомат
 * Студенты:
 * - Максим Покидько
 * - Усейнов Даниэль
 * - Ярослав Епишенко
 * 10 января 2024 г.
 */

package main

import (
	"fmt"
	"io"
	"log"
	"net/http"
)

func main() {
	url := "localhost:8080"
	router := http.NewServeMux()
	router.HandleFunc("/", open)
	router.HandleFunc("/status", status)

	fs := http.FileServer(http.Dir("FrontEnd"))
	router.Handle("/FrontEnd/", http.StripPrefix("/FrontEnd/", fs))

	log.Println("Сервер работает на порту 8080")
	err := http.ListenAndServe(url, router)
	if err != nil {
		log.Fatal(err)
	}
	//
	resp, err := http.Get(url)
	if err != nil {
		fmt.Println("Ошибка при выполнении GET запроса:", err)
		return
	}
	defer resp.Body.Close()

	body, err := io.ReadAll(resp.Body)
	if err != nil {
		fmt.Println("Ошибка при чтении ответа:", err)
		return
	}

	log.Println("Статус кода:", resp.Status)
	log.Println("Тело ответа:", string(body))
}

func open(w http.ResponseWriter, r *http.Request) {
	// Запуск сервера
	http.ServeFile(w, r, "FrontEnd/index.html")
}

func status(w http.ResponseWriter, r *http.Request) {
	// Статус
	fmt.Fprint(w, "Тест")
}
