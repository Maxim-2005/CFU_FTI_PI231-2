#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <iostream>
#include <vector>
#include <numeric>   // Для std::accumulate
#include <algorithm> // Для std::max_element, std::transform
#include <cmath>     // Для std::round
#include <iterator>  // Для std::ostream_iterator
#include <string>    // Для работы со строкой фамилии

using namespace bsoncxx::builder::stream;

/**
 * @brief Структура для хранения результатов вычислений для одного студента.
 * Используется для возврата нескольких значений из чистой функции.
 */
struct StudentScores {
    int avg_score;
    int max_score;
};

/**
 * @brief Чистая функция для вычисления среднего и максимального балла из BSON-массива.
 *
 * Эта функция реализует функциональную логику "Map-Reduce" для массива баллов,
 * используя стандартные алгоритмы C++.
 *
 * @param score_array Представление BSON-массива с баллами.
 * @return StudentScores Структура с рассчитанными средним и максимальным баллами.
 */
StudentScores calculate_scores(const bsoncxx::array::view& score_array) {
    if (score_array.empty()) {
        return { 0, 0 };
    }

    // 1. Отображение (Map): Преобразование BSON-элементов в стандартный вектор int.
    std::vector<int> scores;
    std::transform(
        score_array.begin(),
        score_array.end(),
        std::back_inserter(scores),
        // Лямбда-функция для извлечения int из BSON-элемента
        [](const bsoncxx::array::element& element) -> int {
            if (element && element.type() == bsoncxx::type::k_int32) {
                return element.get_int32().value;
            }
            return 0;
        }
    );

    // 2. Редукция (Reduce): Вычисление суммы с помощью std::accumulate.
    long long total_score = std::accumulate(scores.begin(), scores.end(), 0LL);

    // 3. Вычисление максимального элемента с помощью std::max_element.
    // std::max_element возвращает итератор, его разыменовывание дает значение.
    int max_score = *std::max_element(scores.begin(), scores.end());

    // 4. Расчет среднего балла (с округлением)
    int avg_score = static_cast<int>(std::round(static_cast<double>(total_score) / scores.size()));

    return { avg_score, max_score };
}

int main()
{
    // Установка локали для вывода на русском языке
    std::setlocale(LC_ALL, "Russian");

    // Инициализация MongoDB (RAII - функциональный подход к управлению ресурсами)
    mongocxx::instance instance{};
    mongocxx::client client{ mongocxx::uri{"mongodb://localhost:27017"} };
    auto collection = client["Student_List"]["first"];

    // Вектор для сбора средних баллов (Фамилия на 'A')
    std::vector<int> avg_score_A_results;

    // Вектор для сбора максимальных баллов (Возраст < 19 И MaxScore < 70)
    std::vector<int> max_score_filtered_results;

    // Итерация по курсору с фильтрацией и маппингом
    for (const auto& doc : collection.find({})) {

        // Предварительная проверка наличия массива оценок
        bool has_valid_scores = doc["score"] && doc["score"].type() == bsoncxx::type::k_array;

        // Проверка наличия и типа возраста
        bool has_valid_age = doc["age"] && doc["age"].type() == bsoncxx::type::k_int32;

        // Проверка наличия и типа фамилии
        bool has_valid_surname = doc["surname"] && doc["surname"].type() == bsoncxx::type::k_string;

        if (has_valid_scores) {
            // Маппинг: Применяем чистую функцию расчета баллов один раз для каждого документа
            const auto scores = calculate_scores(doc["score"].get_array().value);

            // --- Функциональный поток 1: Фильтрация по фамилии на 'A' ---
            if (has_valid_surname) {
                // Извлечение фамилии (корректное преобразование string_view в std::string)
                std::string surname = static_cast<std::string>(doc["surname"].get_string().value);

                // Предикат (Filter): Фамилия не пуста и начинается с 'A'
                if (!surname.empty() && surname[0] == 'A') {
                    // Маппинг (Map): Сохраняем средний балл
                    avg_score_A_results.push_back(scores.avg_score);
                }
            }

            // --- Функциональный поток 2: Фильтрация по возрасту < 19 И MaxScore < 70 ---

            // Предикат 1: Возраст меньше 19
            bool is_under_19 = has_valid_age && doc["age"].get_int32().value < 19;

            // Предикат 2: Максимальный балл меньше 70
            bool is_max_score_under_70 = scores.max_score < 70;

            // Комбинированный предикат (Filter)
            if (is_under_19 && is_max_score_under_70) {
                // Маппинг (Map): Сохраняем максимальный балл
                max_score_filtered_results.push_back(scores.max_score);
            }
        }
    }

    // Вывод результатов с использованием функционального отображения (std::transform)

    // 1. Вывод средних баллов студентов с фамилией на 'A'
    std::cout << "Средние баллы студентов с фамилией на A: ";
    std::transform(
        avg_score_A_results.begin(),
        avg_score_A_results.end(),
        std::ostream_iterator<int>(std::cout, " "), // Отображение элементов в cout
        [](int score) { return score; } // Лямбда-проекция
    );

    // 2. Вывод максимальных баллов студентов с возрастом меньше 19 и максимальным баллом меньше 70
    std::cout << "\nМаксимальные баллы студентов с возрастом меньше 19 и максимальным баллом меньше 70: ";
    std::transform(
        max_score_filtered_results.begin(),
        max_score_filtered_results.end(),
        std::ostream_iterator<int>(std::cout, " "), // Отображение элементов в cout
        [](int score) { return score; } // Лямбда-проекция
    );
    std::cout << "\n";

    return 0;
}