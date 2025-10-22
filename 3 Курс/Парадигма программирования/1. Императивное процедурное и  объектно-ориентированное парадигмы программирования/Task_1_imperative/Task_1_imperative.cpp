#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include <iomanip> // для std::fixed и std::setprecision

using json = nlohmann::json;

// Структура для хранения данных студента
struct Student {
    std::string name;
    int age;
    double averageGrade;
};

// Функция для вывода информации о студенте
void printStudent(const Student& student) {
    std::cout << "Name: " << student.name
        << ", Age: " << student.age
        << ", Average grade: " << student.averageGrade << std::endl;
}

// Функция для проверки критериев фильтрации
bool meetsCriteria(const Student& student) {
    return student.age < 19 && student.averageGrade > 4.0;
}

// Функция для проверки возраста меньше 19
bool isUnder19(const Student& student) {
    return student.age < 19;
}

// Функция для получения студентов младше 19 лет
std::vector<Student> getStudentsUnder19(const std::vector<Student>& students) {
    std::vector<Student> under19Students;

    for (const auto& student : students) {
        if (isUnder19(student)) {
            under19Students.push_back(student);
        }
    }

    return under19Students;
}

// Функция для вычисления среднего балла студентов младше 19 лет
double calculateAverageGradeUnder19(const std::vector<Student>& students) {
    auto under19Students = getStudentsUnder19(students);

    if (under19Students.empty()) {
        return 0.0;
    }

    double sum = 0.0;
    for (const auto& student : under19Students) {
        sum += student.averageGrade;
    }

    return sum / under19Students.size();
}

// Функция для нахождения максимального балла среди студентов младше 19 лет
double findMaxGradeUnder19(const std::vector<Student>& students) {
    auto under19Students = getStudentsUnder19(students);

    if (under19Students.empty()) {
        return 0.0;
    }

    double maxGrade = under19Students[0].averageGrade;
    for (const auto& student : under19Students) {
        if (student.averageGrade > maxGrade) {
            maxGrade = student.averageGrade;
        }
    }

    return maxGrade;
}

// Функция для вывода статистики по студентам младше 19 лет
void printUnder19Statistics(const std::vector<Student>& students) {
    auto under19Students = getStudentsUnder19(students);

    if (under19Students.empty()) {
        std::cout << "No students under 19 years found." << std::endl;
        return;
    }

    // Вычисляем статистику
    double averageGrade = calculateAverageGradeUnder19(students);
    double maxGrade = findMaxGradeUnder19(students);

    // Выводим статистику
    std::cout << "\n=== Statistics for students under 19 years ===" << std::endl;
    std::cout << "Total students under 19: " << under19Students.size() << std::endl;
    std::cout << std::fixed << std::setprecision(2); // Форматируем вывод чисел
    std::cout << "Average grade of students under 19: " << averageGrade << std::endl;
    std::cout << "Maximum grade among students under 19: " << maxGrade << std::endl;

    // Выводим студентов с максимальным баллом
    std::cout << "\nStudent(s) with maximum grade:" << std::endl;
    for (const auto& student : under19Students) {
        if (student.averageGrade == maxGrade) {
            printStudent(student);
        }
    }
}

// Функция для вывода всех студентов младше 19 лет
void printStudentsUnder19(const std::vector<Student>& students) {
    auto under19Students = getStudentsUnder19(students);

    if (under19Students.empty()) {
        std::cout << "No students under 19 years found." << std::endl;
        return;
    }

    std::cout << "\nStudents under 19 years:" << std::endl;
    std::cout << "=========================" << std::endl;
    for (const auto& student : under19Students) {
        printStudent(student);
    }
    std::cout << "Total: " << under19Students.size() << " students." << std::endl;
}

// Функция для парсинга JSON файла
bool parseJSONFile(const std::string& filename, std::vector<Student>& students) {
    try {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Cannot open file " << filename << std::endl;
            return false;
        }

        json jsonData;
        file >> jsonData;

        // Очищаем вектор студентов
        students.clear();

        // Обрабатываем разные форматы JSON
        json studentArray;

        if (jsonData.is_array()) {
            // Формат 1: Прямой массив студентов
            studentArray = jsonData;
        }
        else if (jsonData.is_object() && jsonData.contains("students")) {
            // Формат 2: Объект с полем "students"
            studentArray = jsonData["students"];
        }
        else {
            std::cerr << "Error: Unknown JSON format" << std::endl;
            return false;
        }

        // Парсим данные студентов
        for (const auto& studentData : studentArray) {
            Student student;

            // Проверяем наличие обязательных полей
            if (!studentData.contains("name") ||
                !studentData.contains("age") ||
                !studentData.contains("average_grade")) {
                std::cerr << "Warning: Student missing required fields, skipping" << std::endl;
                continue;
            }

            student.name = studentData["name"];
            student.age = studentData["age"];
            student.averageGrade = studentData["average_grade"];

            // Проверяем корректность данных
            if (student.age < 0 || student.age > 100) {
                std::cerr << "Warning: Invalid age for student " << student.name << ", skipping" << std::endl;
                continue;
            }

            if (student.averageGrade < 0 || student.averageGrade > 5.0) {
                std::cerr << "Warning: Invalid average grade for student " << student.name << ", skipping" << std::endl;
                continue;
            }

            students.push_back(student);
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

// Функция для фильтрации студентов
std::vector<Student> filterStudents(const std::vector<Student>& students) {
    std::vector<Student> filteredStudents;

    for (const auto& student : students) {
        if (meetsCriteria(student)) {
            filteredStudents.push_back(student);
        }
    }

    return filteredStudents;
}

// Функция для вывода отфильтрованных студентов
void printFilteredStudents(const std::vector<Student>& students) {
    std::vector<Student> filtered = filterStudents(students);

    if (filtered.empty()) {
        std::cout << "No students found matching the criteria (age < 19 and grade > 4.0)." << std::endl;
        return;
    }

    std::cout << "\nStudents younger than 19 years with average grade above 4.0:" << std::endl;
    std::cout << "=============================================================" << std::endl;

    for (const auto& student : filtered) {
        printStudent(student);
    }

    std::cout << "Total found: " << filtered.size() << " students." << std::endl;
}

// Функция для вывода всех студентов (для отладки)
void printAllStudents(const std::vector<Student>& students) {
    std::cout << "\nAll students:" << std::endl;
    std::cout << "=============" << std::endl;

    for (const auto& student : students) {
        printStudent(student);
    }

    std::cout << "Total: " << students.size() << " students." << std::endl;
}

int main() {
    std::cout << "Imperative Programming - Student Statistics" << std::endl;

    // Переменные для хранения данных
    std::vector<Student> students;
    std::string filename = "base.json";

    // Основной поток выполнения
    std::cout << "Starting student parser..." << std::endl;

    // Парсим JSON файл
    if (!parseJSONFile(filename, students)) {
        std::cerr << "Failed to process file " << filename << std::endl;
        return 1;
    }

    // Выводим всех студентов младше 19 лет
    printStudentsUnder19(students);

    // Выводим статистику по студентам младше 19 лет
    printUnder19Statistics(students);

    // Выводим отфильтрованных студентов (оригинальный критерий)
    printFilteredStudents(students);

    return 0;
}