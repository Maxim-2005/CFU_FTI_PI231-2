#include <iostream>
#include <string>

class Document {
    std::string data;
public:
    Document(std::string data) :data(data) {
    }

    const std::string& get() const {
        return data;
    }
};

class PrintStrategy {
public:
    virtual void print(const Document& document) = 0;
};


class Printer {
    PrintStrategy* strategy;

public:
    Printer(PrintStrategy* strategy) :strategy(strategy) {
    }

    void setStrategy(PrintStrategy* strategy) {
        delete this->strategy;
        this->strategy = strategy;
    }

    void print(const Document& doc) {
        if (strategy == nullptr) exit(1);

        strategy->print(doc);
    }

    ~Printer() {
        delete strategy;
    }
};

// Ваш код здесь

// реализация класса ScreenPrintStrategy
class ScreenPrintStrategy : public PrintStrategy {
public:
    void print(const Document& document) {
        std::cout << document.get() << std::endl; // вывод построчно
    };
};

int s = 0;
// реализация класса StringPrintStrategy
class StringPrintStrategy : public PrintStrategy {
public:
    void print(const Document& document) {
        s++;
        std::cout << "--- doc " << std::to_string(s) << " ---" << std::endl; // вывод с форматированием
        std::cout << document.get() << std::endl;
    };

    std::string getPrintedDocuments() const {
        return ""; //"--- doc " + std::to_string(s) + " ---\n";
    };
};

int m = 0;
// реализация класса MockPrintStrategy
class MockPrintStrategy : public PrintStrategy {
public:
    void print(const Document& document) {
        m++; // колличество копий
    };

    int getPrintedDocumentsCount() const {
        return m;
    };
};

//

int main() {
    Printer printer(new ScreenPrintStrategy());

    int count;
    std::cin >> count; std::cin.ignore(1);
    while (count--) {
        std::string data;
        std::getline(std::cin, data);
        printer.print(Document(data)); // Печать документа на экран
    }

    StringPrintStrategy* stringStrategy = new StringPrintStrategy();
    printer.setStrategy(stringStrategy);
    std::cin >> count; std::cin.ignore(1);
    while (count--) {
        std::string data;
        std::getline(std::cin, data);
        printer.print(Document(data)); // Печать документа в строку
    }
    std::cout << stringStrategy->getPrintedDocuments() << std::endl;

    MockPrintStrategy* mockStrategy = new MockPrintStrategy();
    printer.setStrategy(mockStrategy);
    std::cin >> count; std::cin.ignore(1);
    while (count--) {
        std::string data;
        std::getline(std::cin, data);
        printer.print(Document(data)); // Имитация печати, на самом деле просто подсчёт
    }
    std::cout << mockStrategy->getPrintedDocumentsCount() << std::endl;
}
