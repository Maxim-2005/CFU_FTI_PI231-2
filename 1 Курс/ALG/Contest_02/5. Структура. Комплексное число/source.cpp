Complex make_complex(std::string num) {

    // разбиение комплексного числа
    bool is_minus = false;
    bool is_plus = false;
    std::string first;
    std::string second;
    for (char c : num) {
        if (c == '-') {
            is_minus = true;
            continue;

        }
        else if (c == '+') {
            is_plus = true;
            continue;
        }
        if (!(is_plus || is_minus) && c != ' ') {
            first += c;
        }
        else if ((is_plus || is_minus) && c != ' ') {
            if (first.length() == 0) {
                first += '-';
                first += c;
                is_minus = false;
                continue;
            }
            second += c;
        }
    }
    double re = std::stod(first);
    double im = std::stod(second);
    if (is_minus) {
        im *= -1;
    }
    Complex complex;
    complex.re = re;
    complex.im = im;
    return complex;

}

// вычисление суммы комплексных чисел
Complex sum(Complex left, Complex right) {
    double f = left.re + right.re;
    double s = left.im + right.im;
    if (left.im + right.im == 0){
        s = 0.;
    }
    return Complex{f,s };
}

// вычисление разности комплексных чисел
Complex sub(Complex left, Complex right) {
    return Complex{ left.re - right.re, left.im - right.im };
}

// умножение комплексных чисел
Complex mul(Complex left, Complex right) {
    double f = left.re * right.re - left.im * right.im;
    double s = left.re * right.im + left.im * right.re;
    return Complex{f,s };
}

// деление комплексных чисел
Complex div(Complex left, Complex right ) {
    return Complex{(left.re*right.re + left.im*right.im)/(right.re*right.re + right.im*right.im), (left.im*right.re - left.re*right.im)/ (right.re * right.re + right.im * right.im) };
}

// вывод комплексных чисел
void print(Complex num) {
    double re, im;
    re = num.re;
    im = num.im;
    std::cout << re;
    if (im >= 0) {
        std::cout << "+";
    }
    std::cout << im << "j\n";

}