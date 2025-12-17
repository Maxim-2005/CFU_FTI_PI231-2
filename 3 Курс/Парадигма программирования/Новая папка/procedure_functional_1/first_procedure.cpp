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

    // Векторы для сбора результатов (эквивалент av_scAr и max_scAr из процедурного кода)
    std::vector<int> av_scAr;
    std::vector<int> max_scAr;

    // Итерация по курсору с фильтрацией и маппингом
    for (const auto& doc : collection.find({})) {

        // Предикат (Filter): Возраст меньше 19
        bool is_under_19 = doc["age"] && doc["age"].type() == bsoncxx::type::k_int32 &&
            doc["age"].get_int32().value < 19;

        // Предварительная проверка наличия массива оценок
        bool has_valid_scores = doc["score"] && doc["score"].type() == bsoncxx::type::k_array;

        if (is_under_19 && has_valid_scores) {
            // Маппинг: Применяем чистую функцию расчета баллов
            const auto scores = calculate_scores(doc["score"].get_array().value);

            // Сохраняем результаты
            av_scAr.push_back(scores.avg_score);
            max_scAr.push_back(scores.max_score);
        }
    }

    // Вывод результатов с использованием функционального отображения (std::transform)

    // 1. Вывод средних баллов
    std::cout << "Средние баллы студентов с возрастом меньше 19: ";
    // Используем std::transform и std::ostream_iterator для декларативного вывода
    std::transform(
        av_scAr.begin(),
        av_scAr.end(),
        std::ostream_iterator<int>(std::cout, " "),
        [](int score) { return score; }
    );

    // 2. Вывод максимальных баллов
    std::cout << "\nМаксимальные баллы студентов с возрастом меньше 19: ";
    // Используем std::transform и std::ostream_iterator для декларативного вывода
    std::transform(
        max_scAr.begin(),
        max_scAr.end(),
        std::ostream_iterator<int>(std::cout, " "),
        [](int score) { return score; }
    );
    std::cout << "\n";

    return 0;
}