#include <iostream>
#include <vector>

// класс фигуры
class Shape {
public:
	// Контсруктор по умолчанию
    Shape() {};

	// виртуальный метод расчета периметра
    virtual double getPerimeter() {
        return .0;
    };
};

// класс фигуры прямоугольника
class Rectangle : public Shape {
public:
    int a, b;
	
	// Контсруктор прямоугольника
    Rectangle(int a, int b) {
        this->a = a;
        this->b = b;
    }

	// переопределение метода расчета периметра для прямоугольника
    double getPerimeter() override {
        return (this->a * 2) + (this->b * 2);
    };
};

// класс фигуры круга
class Circle : public Shape {
public:
    int r;
    double pi = 3.141592653589793;

	// Контсруктор круга
    Circle(int r) {
        this->r = r;
    }

	// переопределение метода расчета периметра для круга
    double getPerimeter() override {
        return (2 * pi) * this->r;
    };
};

// класс фигуры треугольника
class Triangle : public Shape {
public:
    int a, b, c;

	// Контсруктор треугольника
    Triangle(int a, int b, int c) {
        this->a = a;
        this->b = b;
        this->c = c;
    }

	// переопределение метода расчета периметра для треугольника
    double getPerimeter() override {
        if (a + b > c && b + c > a && c + a > b) {
            return this->a + this->b + this->c;
        }
        else {
            return 0;
        }
    };
};


int main(){
    int momentum;
    std::cin >> momentum;
    srand(momentum);
    std::vector <Shape*> shapes(rand() % 100 + 1);
    for (int i=0; i < shapes.size(); i++){
        int a = rand()%10 + 1, b = rand()%10 + 1, c = rand()%10 + 1;
        if (rand() % 3 == 0) shapes[i] = new Rectangle(a, b);
        else if (rand() % 3 == 1) shapes[i] = new Circle(c);
        else shapes[i] = new Triangle(a, b, c);
    }
    
    double sum = 0;
    for (auto shape : shapes) { sum += shape->getPerimeter();}
    std::cout << (int)sum;
}
