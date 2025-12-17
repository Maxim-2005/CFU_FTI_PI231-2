#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <iterator>
#include <string>

using namespace bsoncxx::builder::stream;

struct StudentScores {
    int avg_score;
    int max_score;
};

StudentScores calculate_scores(const bsoncxx::array::view& score_array) {
    if (score_array.empty()) {
        return { 0, 0 };
    }

    std::vector<int> scores;
    std::transform(
        score_array.begin(),
        score_array.end(),
        std::back_inserter(scores),
        [](const bsoncxx::array::element& element) -> int {
            if (element && element.type() == bsoncxx::type::k_int32) {
                return element.get_int32().value;
            }
            return 0;
        }
    );

    long long total_score = std::accumulate(scores.begin(), scores.end(), 0LL);

    int max_score = *std::max_element(scores.begin(), scores.end());

    int avg_score = static_cast<int>(std::round(static_cast<double>(total_score) / scores.size()));

    return { avg_score, max_score };
}

int main()
{
    std::setlocale(LC_ALL, "Russian");

    mongocxx::instance instance{};
    mongocxx::client client{ mongocxx::uri{"mongodb://localhost:27017"} };
    auto collection = client["Student_List"]["first"];

    std::vector<int> avg_score_A_results;
    std::vector<int> max_score_filtered_results;
    for (const auto& doc : collection.find({})) {
        bool has_valid_scores = doc["score"] && doc["score"].type() == bsoncxx::type::k_array;

        if (has_valid_scores) {
            const auto scores = calculate_scores(doc["score"].get_array().value);

            bool is_surname_valid = doc["surname"] && doc["surname"].type() == bsoncxx::type::k_string;
            if (is_surname_valid) {
                std::string surname = static_cast<std::string>(doc["surname"].get_string().value);

                if (!surname.empty() && surname[0] == 'A') {
                    avg_score_A_results.push_back(scores.avg_score);
                }
            }

            bool is_under_19 = doc["age"] && doc["age"].type() == bsoncxx::type::k_int32 &&
                doc["age"].get_int32().value < 19;

            bool is_max_score_under_70 = scores.max_score < 70;

            if (is_under_19 && is_max_score_under_70) {
                max_score_filtered_results.push_back(scores.max_score);
            }
        }
    }

    std::cout << "—редние баллы студентов с фамилией на A: ";
    std::transform(
        avg_score_A_results.begin(),
        avg_score_A_results.end(),
        std::ostream_iterator<int>(std::cout, " "),
        [](int score) { return score; }
    );

    std::cout << "\nћаксимальные баллы студентов с возрастом меньше 19 и максимальным баллом меньше 70: ";
    std::transform(
        max_score_filtered_results.begin(),
        max_score_filtered_results.end(),
        std::ostream_iterator<int>(std::cout, " "),
        [](int score) { return score; }
    );
    std::cout << "\n";

    return 0;
}