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
    // �����������
    Student(const std::string& name, int age, double averageGrade)
        : name(name), age(age), averageGrade(averageGrade) {
    }

    // �������
    std::string getName() const { return name; }
    int getAge() const { return age; }
    double getAverageGrade() const { return averageGrade; }

    // ����� ��� �������� ������� ����������
    bool meetsCriteria() const {
        return age < 19 && averageGrade > 4.0;
    }

    // ����� ��� �������� �������� ������ 19
    bool isUnder19() const {
        return age < 19;
    }

    // ����� ��� ������ ���������� � ��������
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
    // ����� ��� �������� JSON �����
    bool parseFromFile(const std::string& filename) {
        try {
            std::ifstream file(filename);
            if (!file.is_open()) {
                std::cerr << "Error: Cannot open file " << filename << std::endl;
                return false;
            }

            json jsonData;
            file >> jsonData;

            // ������� ������� ������ ���������
            students.clear();

            // ��������� ������ ������� JSON
            if (jsonData.is_array()) {
                // ������ 1: ������ ������ ���������
                parseStudentArray(jsonData);
            }
            else if (jsonData.is_object() && jsonData.contains("students")) {
                // ������ 2: ������ � ����� "students"
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
    // ����� ��� �������� ������� ���������
    void parseStudentArray(const json& studentArray) {
        for (const auto& studentData : studentArray) {
            try {
                // ��������� ������� ������������ �����
                if (!studentData.contains("name") ||
                    !studentData.contains("age") ||
                    !studentData.contains("average_grade")) {
                    std::cerr << "Warning: Student missing required fields, skipping" << std::endl;
                    continue;
                }

                std::string name = studentData["name"];
                int age = studentData["age"];
                double averageGrade = studentData["average_grade"];

                // ��������� ������������ ������
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
    // ����� ��� ��������� ��������� ������ 19 ���
    std::vector<Student> getStudentsUnder19() const {
        std::vector<Student> under19Students;

        for (const auto& student : students) {
            if (student.isUnder19()) {
                under19Students.push_back(student);
            }
        }

        return under19Students;
    }

    // ����� ��� ���������� �������� ����� ��������� ������ 19 ���
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

    // ����� ��� ���������� ������������� ����� ����� ��������� ������ 19 ���
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

    // ����� ��� ������ ���������� �� ��������� ������ 19 ���
    void displayUnder19Statistics() const {
        auto under19Students = getStudentsUnder19();

        if (under19Students.empty()) {
            std::cout << "No students under 19 years found." << std::endl;
            return;
        }

        // ��������� ����������
        double averageGrade = calculateAverageGradeUnder19();
        double maxGrade = findMaxGradeUnder19();

        // ������� ����������
        std::cout << "\n=== Statistics for students under 19 years ===" << std::endl;
        std::cout << "Total students under 19: " << under19Students.size() << std::endl;
        std::cout << std::fixed << std::setprecision(2); // ����������� ����� �����
        std::cout << "Average grade of students under 19: " << averageGrade << std::endl;
        std::cout << "Maximum grade among students under 19: " << maxGrade << std::endl;

        // ������� ��������� � ������������ ������
        std::cout << "\nStudent(s) with maximum grade:" << std::endl;
        for (const auto& student : under19Students) {
            if (student.getAverageGrade() == maxGrade) {
                student.display();
            }
        }
    }

    // ����� ��� ������ ���� ��������� ������ 19 ���
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

    // ����� ��� ������ ��������������� ��������� (������������ ��������)
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

    // ����� ��� ���������� ��������� �� ��������� (������� < 19 � ������ > 4.0)
    std::vector<Student> filterStudents() const {
        std::vector<Student> filteredStudents;

        for (const auto& student : students) {
            if (student.meetsCriteria()) {
                filteredStudents.push_back(student);
            }
        }

        return filteredStudents;
    }

    // ������ ��� ���� ���������
    const std::vector<Student>& getAllStudents() const {
        return students;
    }
};

int main() {
    std::cout << "Student Statistics - Proedure Approach" << std::endl;
    StudentParser parser;

    // ������ JSON ����
    if (parser.parseFromFile("base.json")) {
        // ������� ���� ��������� ������ 19 ���
        parser.displayStudentsUnder19();

        // ������� ���������� �� ��������� ������ 19 ���
        parser.displayUnder19Statistics();

        // �������������: ������� ��������� �� ������������� ��������
        parser.displayFilteredStudents();
    }
    else {
        std::cerr << "Failed to process file." << std::endl;
        return 1;
    }

    return 0;
}