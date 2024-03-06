#include <iostream>
#include <string>
#include <sstream>

class Complex {
public:
    double re; // вещественная часть
    double im; // мнимая часть

    // конструктор из строки
    Complex (std::string num) {
        std::stringstream ss(num);
        ss >> re;

        std::string im_str;
        ss >> im_str;
        if (im_str.length() == 1) {
            std::string temp;
            ss >> temp;
            im_str += temp;
        }

        im = std::stod(im_str);

        if (re == -0) 
            re = 0;
        if (im == -0) 
            im = 0;
    }

    // сложение комплексных чисел
    Complex operator+(Complex other) const {
        Complex res("0+0j");
        res.re = this->re + other.re;
        res.im = this->im + other.im;
        return res;  
    }

    // вычитание комплексных чисел
    Complex operator-(Complex other) const {
        Complex res("0+0j");
        res.re = this->re - other.re;
        res.im = this->im - other.im;
        return res;
    }

    // умножение комплексных чисел
    Complex operator*(Complex other) const {
        Complex res("0+0j");
        res.re = this->re * other.re - this->im * other.im;
        res.im = this->re * other.im + this->im * other.re;
        return res;
    }

    // деление комплексных чисел
    Complex operator/(Complex other) const {
        Complex res("0+0j");
        res.re = (this->re * other.re + this->im * other.im) / (other.re * other.re + other.im * other.im);
        res.im = (this->im * other.re - this->re * other.im) / (other.re * other.re + other.im * other.im);
        return res;
    }

    // подключение функции вывода комплексных чисел
    friend std::ostream& operator<<(std::ostream& out, const Complex& num);
};

// вывод комплексных чисел
std::ostream& operator<<(std::ostream& out, const Complex& num) {
    out << (num.re == 0.0 ? 0.0 : num.re)
        << (num.im < 0 ? "" : "+")
        << (num.im == 0.0 ? 0.0 : num.im) << 'j';
    return out;
}

int main()
{
    std::string num;
    std::getline(std::cin, num, 'j');
    Complex c1(num);

    std::getline(std::cin, num, 'j');
    Complex c2(num);

    std::cout << c1 + c2 << '\n' << c1 - c2 << '\n'
        << c1 * c2 << '\n' << c1 / c2 << std::endl;
}