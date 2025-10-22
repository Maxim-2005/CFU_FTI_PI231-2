#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct Student {
    char name[100];
    int age;
    double averageGrade;
};

std::vector<Student> students;
int studentCount = 0;

void addStudent(const char* name, int age, double averageGrade) {
    Student newStudent;
    strcpy_s(newStudent.name, name);
    newStudent.age = age;
    newStudent.averageGrade = averageGrade;
    students.push_back(newStudent);
    studentCount++;
}

void printStudent(const Student* student) {
    std::cout << "Name: " << student->name
        << ", Age: " << student->age
        << ", Average grade: " << student->averageGrade << std::endl;
}

int meetsCriteria(const Student* student) {
    return (student->age < 19 && student->averageGrade > 4.0);
}

int parseJSONFile(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return 0;
    }

    json jsonData;
    file >> jsonData;

    students.clear();
    studentCount = 0;

    json studentArray = jsonData.is_array() ? jsonData : jsonData["students"];

    for (const auto& studentData : studentArray) {
        std::string name = studentData["name"];
        int age = studentData["age"];
        double averageGrade = studentData["average_grade"];
        addStudent(name.c_str(), age, averageGrade);
    }

    return 1;
}

void mainProcedure() {
    if (!parseJSONFile("base.json")) {
        std::cerr << "Failed to process file." << std::endl;
        return;
    }

    std::cout << "Loaded " << studentCount << " students." << std::endl;
    std::cout << "\nStudents younger than 19 years with average grade above 4.0:" << std::endl;
    std::cout << "=============================================================" << std::endl;

    int foundCount = 0;
    for (int i = 0; i < studentCount; i++) {
        if (meetsCriteria(&students[i])) {
            printStudent(&students[i]);
            foundCount++;
        }
    }

    if (foundCount == 0) {
        std::cout << "No students found matching the criteria." << std::endl;
    }
    else {
        std::cout << "Total found: " << foundCount << " students." << std::endl;
    }
}

int main() {
    std::cout << "Procedure" << std::endl;
    mainProcedure();
    return 0;
}