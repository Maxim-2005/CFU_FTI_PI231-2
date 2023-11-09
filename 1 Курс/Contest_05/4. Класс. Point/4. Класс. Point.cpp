#include <iostream>
#include "json.hpp"
using json = nlohmann::json;

class Point {
public:
    double x;
    double y;
    double r;
    double a;

    // конструктор
    Point(double x, double y) {
        this->x = x;
        this->y = y;
        this->r = sqrt(this->x * this->x + this->y * this->y);
        this->a = atan2(this->y, this->x);
    };

    // сеттеры
    void set_x(double x) {
        this->x = x;
        this->r = sqrt(this->x * this->x + this->y * this->y);
        this->a = atan2(this->y, this->x);
    };
    void set_y(double y) {
        this->y = y;
        this->r = sqrt(this->x * this->x + this->y * this->y);
        this->a = atan2(this->y, this->x);
    };
    void set_r(double r) {
        this->r = r;
        this->x = this->r * cos(this->a);
        this->y = this->r * sin(this->a);
    };
    void set_a(double a) {
        this->a = a;
        this->x = this->r * cos(this->a);
        this->y = this->r * sin(this->a);
    };

    // геттеры
    double get_x() {
        return round(this->x * 100000) / 100000;
    };
    double get_y() {
        return round(this->y * 100000) / 100000;
    };
    double get_r() {
        return round(this->r * 100000) / 100000;
    };
    double get_a() {
        return round(this->a * 100000) / 100000;
    };
};

int main() {
    double x, y;
    std::cin >> x >> y;

    Point p(x, y);
    json moves;
    std::cin >> moves;

    for (auto& move : moves) {
        std::string ort = move["ort"];
        double value = move["value"];
        if (ort == "x") p.set_x(p.get_x() + value);
        else if (ort == "y") p.set_y(p.get_y() + value);
        else if (ort == "r") p.set_r(p.get_r() + value);    
        else p.set_a(p.get_a() + value);
        std::cout << round(p.get_x() * (1E+5)) / (1E+5) << ' ' << round(p.get_y() * (1E+5)) / (1E+5) << std::endl;
    }
}