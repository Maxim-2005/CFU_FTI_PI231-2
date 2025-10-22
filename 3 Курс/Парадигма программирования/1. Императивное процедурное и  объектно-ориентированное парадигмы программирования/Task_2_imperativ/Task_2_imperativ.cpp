#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include <iomanip>

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

// Функция для проверки, начинается ли имя на букву A
bool nameStartsWithA(const Student& student) {
    return !student.name.empty() && (student.name[0] == 'A' || student.name[0] == 'a');
}

// Функция для проверки возраста меньше 19 и балла меньше 70
bool isUnder19AndGradeLessThan70(const Student& student) {
    return student.age < 19 && student.averageGrade < 70.0;
}

// Функция для получения студентов, чьи имена начинаются на букву A
std::vector<Student> getStudentsWithNameStartingWithA(const std::vector<Student>& students) {
    std::vector<Student> filteredStudents;

    for (const auto& student : students) {
        if (nameStartsWithA(student)) {
            filteredStudents.push_back(student);
        }
    }

    return filteredStudents;
}

// Функция для вычисления среднего балла студентов, чьи имена начинаются на букву A
double calculateAverageGradeForStudentsWithNameA(const std::vector<Student>& students) {
    auto filteredStudents = getStudentsWithNameStartingWithA(students);

    if (filteredStudents.empty()) {
        return 0.0;
    }

    double sum = 0.0;
    for (const auto& student : filteredStudents) {
        sum += student.averageGrade;
    }

    return sum / filteredStudents.size();
}

// Функция для получения студентов младше 19 лет с баллом меньше 70
std::vector<Student> getStudentsUnder19WithGradeLessThan70(const std::vector<Student>& students) {
    std::vector<Student> filteredStudents;

    for (const auto& student : students) {
        if (isUnder19AndGradeLessThan70(student)) {
            filteredStudents.push_back(student);
        }
    }

    return filteredStudents;
}

// Функция для нахождения максимального балла среди студентов младше 19 лет с баллом меньше 70
double findMaxGradeUnder19AndLessThan70(const std::vector<Student>& students) {
    auto filteredStudents = getStudentsUnder19WithGradeLessThan70(students);

    if (filteredStudents.empty()) {
        return 0.0;
    }

    double maxGrade = filteredStudents[0].averageGrade;
    for (const auto& student : filteredStudents) {
        if (student.averageGrade > maxGrade) {
            maxGrade = student.averageGrade;
        }
    }

    return maxGrade;
}

// Функция для вывода среднего балла студентов с именами на букву A
void printAverageGradeForStudentsWithNameA(const std::vector<Student>& students) {
    auto studentsWithA = getStudentsWithNameStartingWithA(students);
    double averageGrade = calculateAverageGradeForStudentsWithNameA(students);

    std::cout << "\n=== Students with names starting with 'A' ===" << std::endl;

    if (studentsWithA.empty()) {
        std::cout << "No students found with names starting with 'A'." << std::endl;
        return;
    }

    std::cout << "Students with names starting with 'A':" << std::endl;
    std::cout << "======================================" << std::endl;
    for (const auto& student : studentsWithA) {
        printStudent(student);
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\nAverage grade of students with names starting with 'A': " << averageGrade << std::endl;
    std::cout << "Total students: " << studentsWithA.size() << std::endl;
}

// Функция для вывода максимального балла студентов младше 19 лет с баллом меньше 70
void printMaxGradeUnder19AndLessThan70(const std::vector<Student>& students) {
    auto filteredStudents = getStudentsUnder19WithGradeLessThan70(students);
    double maxGrade = findMaxGradeUnder19AndLessThan70(students);

    std::cout << "\n=== Students under 19 years with grade less than 70 ===" << std::endl;

    if (filteredStudents.empty()) {
        std::cout << "No students found under 19 years with grade less than 70." << std::endl;
        return;
    }

    std::cout << "Students under 19 years with grade less than 70:" << std::endl;
    std::cout << "================================================" << std::endl;
    for (const auto& student : filteredStudents) {
        printStudent(student);
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\nMaximum grade among students under 19 years with grade less than 70: " << maxGrade << std::endl;
    std::cout << "Total students: " << filteredStudents.size() << std::endl;

    // Выводим студентов с максимальным баллом
    std::cout << "\nStudent(s) with maximum grade (" << maxGrade << "):" << std::endl;
    for (const auto& student : filteredStudents) {
        if (student.averageGrade == maxGrade) {
            printStudent(student);
        }
    }
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

            // Проверяем корректность данных (теперь оценка до 100)
            if (student.age < 0 || student.age > 100) {
                std::cerr << "Warning: Invalid age for student " << student.name << ", skipping" << std::endl;
                continue;
            }

            if (student.averageGrade < 0 || student.averageGrade > 100.0) {
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

    // Выводим средний балл студентов с именами на букву A
    printAverageGradeForStudentsWithNameA(students);

    // Выводим максимальный балл студентов младше 19 лет с баллом меньше 70
    printMaxGradeUnder19AndLessThan70(students);

    return 0;
}