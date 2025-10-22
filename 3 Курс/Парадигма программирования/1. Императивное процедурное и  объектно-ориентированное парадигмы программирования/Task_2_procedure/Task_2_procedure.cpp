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

    // Метод для проверки, начинается ли имя на букву A
    bool nameStartsWithA() const {
        return !name.empty() && (name[0] == 'A' || name[0] == 'a');
    }

    // Метод для проверки возраста меньше 19 и балла меньше 70
    bool isUnder19AndGradeLessThan70() const {
        return age < 19 && averageGrade < 70.0;
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

                // Проверяем корректность данных (теперь оценка до 100)
                if (age < 0 || age > 100) {
                    std::cerr << "Warning: Invalid age for student " << name << ", skipping" << std::endl;
                    continue;
                }

                if (averageGrade < 0 || averageGrade > 100.0) {
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
    // Метод для получения студентов, чьи имена начинаются на букву A
    std::vector<Student> getStudentsWithNameStartingWithA() const {
        std::vector<Student> filteredStudents;

        for (const auto& student : students) {
            if (student.nameStartsWithA()) {
                filteredStudents.push_back(student);
            }
        }

        return filteredStudents;
    }

    // Метод для вычисления среднего балла студентов, чьи имена начинаются на букву A
    double calculateAverageGradeForStudentsWithNameA() const {
        auto filteredStudents = getStudentsWithNameStartingWithA();

        if (filteredStudents.empty()) {
            return 0.0;
        }

        double sum = 0.0;
        for (const auto& student : filteredStudents) {
            sum += student.getAverageGrade();
        }

        return sum / filteredStudents.size();
    }

    // Метод для получения студентов младше 19 лет с баллом меньше 70
    std::vector<Student> getStudentsUnder19WithGradeLessThan70() const {
        std::vector<Student> filteredStudents;

        for (const auto& student : students) {
            if (student.isUnder19AndGradeLessThan70()) {
                filteredStudents.push_back(student);
            }
        }

        return filteredStudents;
    }

    // Метод для нахождения максимального балла среди студентов младше 19 лет с баллом меньше 70
    double findMaxGradeUnder19AndLessThan70() const {
        auto filteredStudents = getStudentsUnder19WithGradeLessThan70();

        if (filteredStudents.empty()) {
            return 0.0;
        }

        double maxGrade = filteredStudents[0].getAverageGrade();
        for (const auto& student : filteredStudents) {
            if (student.getAverageGrade() > maxGrade) {
                maxGrade = student.getAverageGrade();
            }
        }

        return maxGrade;
    }

    // Метод для вывода среднего балла студентов с именами на букву A
    void displayAverageGradeForStudentsWithNameA() const {
        auto studentsWithA = getStudentsWithNameStartingWithA();
        double averageGrade = calculateAverageGradeForStudentsWithNameA();

        std::cout << "\n=== Students with names starting with 'A' ===" << std::endl;

        if (studentsWithA.empty()) {
            std::cout << "No students found with names starting with 'A'." << std::endl;
            return;
        }

        std::cout << "Students with names starting with 'A':" << std::endl;
        std::cout << "======================================" << std::endl; // Исправленная строка
        for (const auto& student : studentsWithA) {
            student.display();
        }

        std::cout << std::fixed << std::setprecision(2);
        std::cout << "\nAverage grade of students with names starting with 'A': " << averageGrade << std::endl;
        std::cout << "Total students: " << studentsWithA.size() << std::endl;
    }

    // Метод для вывода максимального балла студентов младше 19 лет с баллом меньше 70
    void displayMaxGradeUnder19AndLessThan70() const {
        auto filteredStudents = getStudentsUnder19WithGradeLessThan70();
        double maxGrade = findMaxGradeUnder19AndLessThan70();

        std::cout << "\n=== Students under 19 years with grade less than 70 ===" << std::endl;

        if (filteredStudents.empty()) {
            std::cout << "No students found under 19 years with grade less than 70." << std::endl;
            return;
        }

        std::cout << "Students under 19 years with grade less than 70:" << std::endl;
        std::cout << "================================================" << std::endl;
        for (const auto& student : filteredStudents) {
            student.display();
        }

        std::cout << std::fixed << std::setprecision(2);
        std::cout << "\nMaximum grade among students under 19 years with grade less than 70: " << maxGrade << std::endl;
        std::cout << "Total students: " << filteredStudents.size() << std::endl;

        // Выводим студентов с максимальным баллом
        std::cout << "\nStudent(s) with maximum grade (" << maxGrade << "):" << std::endl;
        for (const auto& student : filteredStudents) {
            if (student.getAverageGrade() == maxGrade) {
                student.display();
            }
        }
    }

    // Геттер для всех студентов
    const std::vector<Student>& getAllStudents() const {
        return students;
    }
};

int main() {
    std::cout << "Student Statistics - OOP Approach" << std::endl;
    StudentParser parser;

    // Парсим JSON файл
    if (parser.parseFromFile("base.json")) {
        // Выводим средний балл студентов с именами на букву A
        parser.displayAverageGradeForStudentsWithNameA();

        // Выводим максимальный балл студентов младше 19 лет с баллом меньше 70
        parser.displayMaxGradeUnder19AndLessThan70();
    }
    else {
        std::cerr << "Failed to process file." << std::endl;
        return 1;
    }

    return 0;
}