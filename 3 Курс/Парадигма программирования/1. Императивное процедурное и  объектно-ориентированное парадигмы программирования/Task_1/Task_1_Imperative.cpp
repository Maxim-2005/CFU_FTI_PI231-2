#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// ��������� ��� �������� ������ ��������
struct Student {
    std::string name;
    int age;
    double averageGrade;
};

// ������� ��� ������ ���������� � ��������
void printStudent(const Student& student) {
    std::cout << "Name: " << student.name
        << ", Age: " << student.age
        << ", Average grade: " << student.averageGrade << std::endl;
}

// ������� ��� �������� ��������� ����������
bool meetsCriteria(const Student& student) {
    return student.age < 19 && student.averageGrade > 4.0;
}

// ������� ��� �������� JSON �����
bool parseJSONFile(const std::string& filename, std::vector<Student>& students) {
    try {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Cannot open file " << filename << std::endl;
            return false;
        }

        json jsonData;
        file >> jsonData;

        // ������� ������ ���������
        students.clear();

        // ������������ ������ ������� JSON
        json studentArray;

        if (jsonData.is_array()) {
            // ������ 1: ������ ������ ���������
            studentArray = jsonData;
        }
        else if (jsonData.is_object() && jsonData.contains("students")) {
            // ������ 2: ������ � ����� "students"
            studentArray = jsonData["students"];
        }
        else {
            std::cerr << "Error: Unknown JSON format" << std::endl;
            return false;
        }

        // ������ ������ ���������
        for (const auto& studentData : studentArray) {
            Student student;

            // ��������� ������� ������������ �����
            if (!studentData.contains("name") ||
                !studentData.contains("age") ||
                !studentData.contains("average_grade")) {
                std::cerr << "Warning: Student missing required fields, skipping" << std::endl;
                continue;
            }

            student.name = studentData["name"];
            student.age = studentData["age"];
            student.averageGrade = studentData["average_grade"];

            // ��������� ������������ ������
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

// ������� ��� ���������� ���������
std::vector<Student> filterStudents(const std::vector<Student>& students) {
    std::vector<Student> filteredStudents;

    for (const auto& student : students) {
        if (meetsCriteria(student)) {
            filteredStudents.push_back(student);
        }
    }

    return filteredStudents;
}

// ������� ��� ������ ��������������� ���������
void printFilteredStudents(const std::vector<Student>& students) {
    std::vector<Student> filtered = filterStudents(students);

    if (filtered.empty()) {
        std::cout << "No students found matching the criteria." << std::endl;
        return;
    }

    std::cout << "\nStudents younger than 19 years with average grade above 4.0:" << std::endl;
    std::cout << "=============================================================" << std::endl;

    for (const auto& student : filtered) {
        printStudent(student);
    }

    std::cout << "Total found: " << filtered.size() << " students." << std::endl;
}

// ������� ��� ������ ���� ��������� (��� �������)
void printAllStudents(const std::vector<Student>& students) {
    std::cout << "\nAll students:" << std::endl;
    std::cout << "=============" << std::endl;

    for (const auto& student : students) {
        printStudent(student);
    }

    std::cout << "Total: " << students.size() << " students." << std::endl;
}

int main() {
    // ���������� ��� �������� ������
    std::vector<Student> students;
    std::string filename = "base.json";

    // �������� ����� ����������
    std::cout << "Starting student parser..." << std::endl;

    // ������ JSON ����
    if (!parseJSONFile(filename, students)) {
        std::cerr << "Failed to process file " << filename << std::endl;
        return 1;
    }

    // ������� ���� ��������� (�����������)
    // printAllStudents(students);

    // ������� ��������������� ���������
    printFilteredStudents(students);

    return 0;
}