#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <mongocxx/uri.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/types.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::open_document;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::finalize;

class Student {
private:
    int id;
    std::string name;
    int age;
    double averageGrade;
    std::string gender;

public:
    // Конструктор
    Student(int id, const std::string& name, int age, double averageGrade, const std::string& gender)
        : id(id), name(name), age(age), averageGrade(averageGrade), gender(gender) {}

    // Конструктор из BSON документа - ИСПРАВЛЕННЫЙ
    Student(const bsoncxx::document::view& doc) {
        id = doc["id"].get_int32().value;

        // Правильное извлечение строки из BSON
        auto name_value = doc["name"].get_string();
        name = std::string(name_value.value.data(), name_value.value.length());

        age = doc["age"].get_int32().value;
        averageGrade = doc["average_grade"].get_double().value;

        // Правильное извлечение строки из BSON
        auto gender_value = doc["gender"].get_string();
        gender = std::string(gender_value.value.data(), gender_value.value.length());
    }

    // Геттеры
    int getId() const { return id; }
    std::string getName() const { return name; }
    int getAge() const { return age; }
    double getAverageGrade() const { return averageGrade; }
    std::string getGender() const { return gender; }

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
        std::cout << "ID: " << id
            << ", Name: " << name
            << ", Age: " << age
            << ", Grade: " << averageGrade
            << ", Gender: " << gender << std::endl;
    }

    // Метод для создания BSON документа из студента
    bsoncxx::document::value toBSON() const {
        return document{}
            << "id" << id
            << "name" << name
            << "age" << age
            << "average_grade" << averageGrade
            << "gender" << gender
            << finalize;
    }
};

class StudentManager {
private:
    mongocxx::client client;
    mongocxx::database db;
    mongocxx::collection collection;
    std::vector<Student> students;

public:
    // Конструктор с подключением к MongoDB
    StudentManager(const std::string& connection_uri = "mongodb://localhost:27017",
        const std::string& db_name = "student_db",
        const std::string& collection_name = "students")
        : client{ mongocxx::uri{connection_uri} }
        , db{ client[db_name] }
        , collection{ db[collection_name] } {

        loadStudentsFromDB();
    }

    // Загрузка студентов из MongoDB
    bool loadStudentsFromDB() {
        try {
            students.clear();

            auto cursor = collection.find({});

            for (auto&& doc : cursor) {
                try {
                    students.emplace_back(doc);
                }
                catch (const std::exception& e) {
                    std::cerr << "Error parsing student from database: " << e.what() << std::endl;
                    continue;
                }
            }

            std::cout << "Successfully loaded " << students.size() << " students from MongoDB." << std::endl;
            return true;
        }
        catch (const std::exception& e) {
            std::cerr << "Error loading from MongoDB: " << e.what() << std::endl;
            return false;
        }
    }

    // Создание тестовых данных из вашего JSON
    void createSampleData() {
        std::vector<Student> sampleStudents = {
            Student(0, "Vasya", 19, 4.5, "male"),
            Student(1, "Tanya", 23, 3.8, "female"),
            Student(2, "Vanya", 17, 5.0, "male"),
            Student(3, "Dima", 15, 4.1, "male"),
            Student(4, "Vika", 14, 3.5, "female"),
            Student(5, "Kolya", 28, 2.7, "male"),
            Student(6, "Alina", 12, 4.8, "female"),
            Student(7, "Danya", 18, 4.0, "male"),
            Student(8, "Kirill", 21, 3.7, "male"),
            Student(9, "Dasha", 13, 4.4, "female")
        };

        // Очищаем коллекцию перед добавлением
        collection.delete_many({});

        for (const auto& student : sampleStudents) {
            addStudentToDB(student);
        }

        std::cout << "Sample data created successfully!" << std::endl;
    }

    // Добавление студента в базу данных
    bool addStudentToDB(const Student& student) {
        try {
            auto result = collection.insert_one(student.toBSON().view());
            if (result->result().inserted_count() == 1) {
                students.push_back(student);
                return true;
            }
            return false;
        }
        catch (const std::exception& e) {
            std::cerr << "Error adding student to database: " << e.what() << std::endl;
            return false;
        }
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

        std::cout << "\n=== Statistics for students under 19 years ===" << std::endl;
        std::cout << "Total students under 19: " << under19Students.size() << std::endl;

        // Выводим всех студентов младше 19
        std::cout << "\nStudents under 19 years:" << std::endl;
        std::cout << "=========================" << std::endl;
        for (const auto& student : under19Students) {
            student.display();
        }

        // Вычисляем и выводим статистику
        double averageGrade = calculateAverageGradeUnder19();
        double maxGrade = findMaxGradeUnder19();

        std::cout << "\nStatistics:" << std::endl;
        std::cout << "===========" << std::endl;
        std::cout << "Average grade of students under 19: " << averageGrade << std::endl;
        std::cout << "Maximum grade among students under 19: " << maxGrade << std::endl;

        // Находим студента с максимальным баллом
        std::cout << "\nStudent(s) with maximum grade (" << maxGrade << "):" << std::endl;
        for (const auto& student : under19Students) {
            if (student.getAverageGrade() == maxGrade) {
                student.display();
            }
        }
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

    // Прямой запрос к MongoDB для студентов младше 19
    void queryUnder19FromDB() {
        try {
            auto filter = document{} << "age" << open_document << "$lt" << 19 << close_document << finalize;
            auto cursor = collection.find(filter.view());

            std::cout << "\n=== Direct MongoDB query: Students under 19 ===" << std::endl;
            int count = 0;
            for (auto&& doc : cursor) {
                Student student(doc);
                student.display();
                count++;
            }
            std::cout << "Total from direct query: " << count << " students." << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Error in direct query: " << e.what() << std::endl;
        }
    }

    // Геттер для всех студентов
    const std::vector<Student>& getAllStudents() const {
        return students;
    }
};

int main() {
    // Инициализация MongoDB (обязательно!)
    mongocxx::instance instance{};

    std::cout << "Student Statistics - MongoDB Approach" << std::endl;

    try {
        StudentManager manager;

        // Создаем тестовые данные из вашего JSON
        manager.createSampleData();

        // Загружаем данные из MongoDB
        if (manager.loadStudentsFromDB()) {
            // Выводим статистику по студентам младше 19 лет
            manager.displayUnder19Statistics();

            // Дополнительно: выводим студентов по оригинальному критерию
            std::cout << "\n\n";
            manager.displayFilteredStudents();

            // Прямой запрос к MongoDB
            std::cout << "\n\n";
            manager.queryUnder19FromDB();
        }
        else {
            std::cerr << "Failed to load data from MongoDB." << std::endl;
            return 1;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "MongoDB connection error: " << e.what() << std::endl;
        std::cerr << "Make sure MongoDB server is running on localhost:27017" << std::endl;
        return 1;
    }

    return 0;
}