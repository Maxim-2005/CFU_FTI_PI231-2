#include <iostream>
#include <string>
#include <cmath>

class Complex {
private:
    double re;
    double im;
public:
    Complex(std::string num) {
        int pos = num.find('+');
        if (pos == -1) {
            pos = num.find('-');
        }
        re = std::stod(num.substr(0, pos));
        int end = num.find('j');
        im = std::stod(num.substr(pos, end - pos));
    }

    friend std::ostream& operator<<(std::ostream& out, const Complex& num) {
        out << (num.re == 0.0 ? 0.0 : num.re)
            << (num.im < 0 ? "" : "+")
            << (num.im == 0.0 ? 0.0 : num.im) << 'j';
        return out;
    }

    Complex operator+(const Complex& other) {
        Complex res("0+0j");
        res.re = this->re + other.re;
        res.im = this->im + other.im;
        return res;
    }

    Complex operator-(const Complex& other) {
        Complex res("0+0j");
        res.re = this->re - other.re;
        res.im = this->im - other.im;
        return res;
    }

    Complex operator*(const Complex& other) {
        Complex res("0+0j");
        res.re = this->re * other.re - this->im * other.im;
        res.im = this->re * other.im + this->im * other.re;
        return res;
    }

    Complex operator/(const Complex& other) {
        Complex res("0+0j");
        double denominator = pow(other.re, 2) + pow(other.im, 2);
        res.re = (this->re * other.re + this->im * other.im) / denominator;
        res.im = (this->im * other.re - this->re * other.im) / denominator;
        return res;
    }
};

int main2() {
    std::string num1, num2;
    std::cin >> num1 >> num2;
    Complex c1(num1);
    Complex c2(num2);

    std::cout << c1 + c2 << '\n' << c1 - c2 << '\n'
        << c1 * c2 << '\n' << c1 / c2 << std::endl;
}




Complex(std::string input) {
    double re, im;
    std::stringstream ss(input);
    ss >> re;

    std::string im_str;
    ss >> im_str;
    if (im_str.length() == 1) {
        // Read one more time
        std::string temp;
        ss >> temp;
        im_str += temp;
    }

    im = std::stod(im_str);

    // -0 check
    if (re == -0) re = 0;
    if (im == -0) im = 0;

    num = std::complex<double>(re, im);
}