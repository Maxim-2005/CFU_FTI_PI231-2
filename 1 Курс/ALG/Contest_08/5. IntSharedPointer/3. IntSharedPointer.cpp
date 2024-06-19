#include <iostream>

// класс по условию задачи
class IntSharedPointer {
private:
    int* ptr;
    int* ref_count;

public:
	// конструктор
    IntSharedPointer(int* p) : ptr(p), ref_count(new int(1)) {}
	
	// деструктор
    ~IntSharedPointer() {
        (*ref_count)--;
        if (*ref_count == 0) {
            delete ptr;
            delete ref_count;
        }
    }
	
	// переопределние оператора *
    int& operator*() {
        return *ptr;
    }
	
	// копирование
    IntSharedPointer(const IntSharedPointer& other) : ptr(other.ptr), ref_count(other.ref_count) {
        (*ref_count)++;
    }
	
	// переопределение оператора =
    IntSharedPointer& operator=(IntSharedPointer other) {
        std::swap(ptr, other.ptr);
        std::swap(ref_count, other.ref_count);
        return *this;
    }
};

void print(IntSharedPointer p) {
    std::cout << *p << std::endl;
}

void print_with_exception(IntSharedPointer p) {
    std::cout << *p << std::endl;
    if (*p % 2) throw std::string("error");
}

int main() {
    IntSharedPointer p(new int);
    std::cin >> *p;
    p = p;
    print(p);

    IntSharedPointer p2(p);
    std::cin >> *p2;
    print(p);
    print(p2);

    {
        int value;
        std::cin >> value;
        IntSharedPointer p3(new int(value));
        p2 = p3;
    }
    print(p2);

    p = p2;
    try {
        print_with_exception(p);
    }
    catch (const std::string& e) {
        std::cout << e << std::endl;
    }
}
