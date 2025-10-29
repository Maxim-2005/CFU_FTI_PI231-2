#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include <algorithm>
#include <iomanip>

using json = nlohmann::json;

class Student {
private:
    std::string name;
    int age;
    double averageGrade;

public:
    // Конструктор
    Student(const std::string& name, int age, double averageGrade)
        : name(name), age(age), averageGrade(averageGrade) {
    }

    // Геттеры
    std::string getName() const { return name; }
    int getAge() const { return age; }
    double getAverageGrade() const { return averageGrade; }

    // Метод для проверки условий фильтрации
    bool meetsCriteria() const {
        return age < 19 && averageGrade > 4.0;
    }

    // Метод для проверки возраста меньше 19
    bool isUnder19() const {
        return age < 19;
    }

    // Метод для вывода информации о студенте
    void display() const {
        std::cout << "Name: " << name
            << ", Age: " << age
            << ", Average grade: " << averageGrade << std::endl;
    }
};

class StudentParser {
private:
    std::vector<Student> students;

public:
    // Метод для парсинга JSON файла
    bool parseFromFile(const std::string& filename) {
        try {
            std::ifstream file(filename);
            if (!file.is_open()) {
                std::cerr << "Error: Cannot open file " << filename << std::endl;
                return false;
            }

            json jsonData;
            file >> jsonData;

            // Очищаем текущий список студентов
            students.clear();

            // Проверяем разные форматы JSON
            if (jsonData.is_array()) {
                // Формат 1: Прямой массив студентов
                parseStudentArray(jsonData);
            }
            else if (jsonData.is_object() && jsonData.contains("students")) {
                // Формат 2: Объект с полем "students"
                parseStudentArray(jsonData["students"]);
            }
            else {
                std::cerr << "Error: Unknown JSON format" << std::endl;
                return false;
            }

            std::cout << "Successfully loaded " << students.size() << " students." << std::endl;
            return true;

        }
        catch (const json::exception& e) {
            std::cerr << "JSON parse error: " << e.what() << std::endl;
            return false;
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return false;
        }
    }

private:
    // Метод для парсинга массива студентов
    void parseStudentArray(const json& studentArray) {
        for (const auto& studentData : studentArray) {
            try {
                // Проверяем наличие обязательных полей
                if (!studentData.contains("name") ||
                    !studentData.contains("age") ||
                    !studentData.contains("average_grade")) {
                    std::cerr << "Warning: Student missing required fields, skipping" << std::endl;
                    continue;
                }

                std::string name = studentData["name"];
                int age = studentData["age"];
                double averageGrade = studentData["average_grade"];

                // Проверяем корректность данных
                if (age < 0 || age > 100) {
                    std::cerr << "Warning: Invalid age for student " << name << ", skipping" << std::endl;
                    continue;
                }

                if (averageGrade < 0 || averageGrade > 5.0) {
                    std::cerr << "Warning: Invalid average grade for student " << name << ", skipping" << std::endl;
                    continue;
                }

                students.emplace_back(name, age, averageGrade);
            }
            catch (const json::exception& e) {
                std::cerr << "Warning: Error parsing student data: " << e.what() << ", skipping" << std::endl;
                continue;
            }
        }
    }

public:
    // Метод для получения студентов младше 19 лет
    std::vector<Student> getStudentsUnder19() const {
        std::vector<Student> under19Students;

        for (const auto& student : students) {
            if (student.isUnder19()) {
                under19Students.push_back(student);
            }
        }

        return under19Students;
    }

    // Метод для вычисления среднего балла студентов младше 19 лет
    double calculateAverageGradeUnder19() const {
        auto under19Students = getStudentsUnder19();

        if (under19Students.empty()) {
            return 0.0;
        }

        double sum = 0.0;
        for (const auto& student : under19Students) {
            sum += student.getAverageGrade();
        }

        return sum / under19Students.size();
    }

    // Метод для нахождения максимального балла среди студентов младше 19 лет
    double findMaxGradeUnder19() const {
        auto under19Students = getStudentsUnder19();

        if (under19Students.empty()) {
            return 0.0;
        }

        double maxGrade = under19Students[0].getAverageGrade();
        for (const auto& student : under19Students) {
            if (student.getAverageGrade() > maxGrade) {
                maxGrade = student.getAverageGrade();
            }
        }

        return maxGrade;
    }

    // Метод для вывода статистики по студентам младше 19 лет
    void displayUnder19Statistics() const {
        auto under19Students = getStudentsUnder19();

        if (under19Students.empty()) {
            std::cout << "No students under 19 years found." << std::endl;
            return;
        }

        // Вычисляем статистику
        double averageGrade = calculateAverageGradeUnder19();
        double maxGrade = findMaxGradeUnder19();

        // Выводим статистику
        std::cout << "\n=== Statistics for students under 19 years ===" << std::endl;
        std::cout << "Total students under 19: " << under19Students.size() << std::endl;
        std::cout << std::fixed << std::setprecision(2); // Форматируем вывод чисел
        std::cout << "Average grade of students under 19: " << averageGrade << std::endl;
        std::cout << "Maximum grade among students under 19: " << maxGrade << std::endl;

        // Выводим студентов с максимальным баллом
        std::cout << "\nStudent(s) with maximum grade:" << std::endl;
        for (const auto& student : under19Students) {
            if (student.getAverageGrade() == maxGrade) {
                student.display();
            }
        }
    }

    // Метод для вывода всех студентов младше 19 лет
    void displayStudentsUnder19() const {
        auto under19Students = getStudentsUnder19();

        if (under19Students.empty()) {
            std::cout << "No students under 19 years found." << std::endl;
            return;
        }

        std::cout << "\nStudents under 19 years:" << std::endl;
        std::cout << "=========================" << std::endl;
        for (const auto& student : under19Students) {
            student.display();
        }
        std::cout << "Total: " << under19Students.size() << " students." << std::endl;
    }

    // Метод для вывода отфильтрованных студентов (оригинальный критерий)
    void displayFilteredStudents() const {
        auto filtered = filterStudents();

        if (filtered.empty()) {
            std::cout << "No students found matching the criteria (age < 19 and grade > 4.0)." << std::endl;
            return;
        }

        std::cout << "\nStudents younger than 19 years with average grade above 4.0:" << std::endl;
        std::cout << "=============================================================" << std::endl;

        for (const auto& student : filtered) {
            student.display();
        }

        std::cout << "Total found: " << filtered.size() << " students." << std::endl;
    }

    // Метод для фильтрации студентов по критериям (возраст < 19 и оценка > 4.0)
    std::vector<Student> filterStudents() const {
        std::vector<Student> filteredStudents;

        for (const auto& student : students) {
            if (student.meetsCriteria()) {
                filteredStudents.push_back(student);
            }
        }

        return filteredStudents;
    }

    // Геттер для всех студентов
    const std::vector<Student>& getAllStudents() const {
        return students;
    }
};

int main() {
    std::cout << "Student Statistics - Proedure Approach" << std::endl;
    StudentParser parser;

    // Парсим JSON файл
    if (parser.parseFromFile("base.json")) {
        // Выводим всех студентов младше 19 лет
        parser.displayStudentsUnder19();

        // Выводим статистику по студентам младше 19 лет
        parser.displayUnder19Statistics();

        // Дополнительно: выводим студентов по оригинальному критерию
        parser.displayFilteredStudents();
    }
    else {
        std::cerr << "Failed to process file." << std::endl;
        return 1;
    }

    return 0;
}