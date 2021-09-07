//
// Created by int.xuqian.zhu on 8/5/2021.
//
#include <iostream>

class Rational {
public:
    Rational(int numerator=0, int denominator=1)
        : numerator_(numerator), denominator_(denominator) {
        std::cout << "Rational constructor." << std::endl;
    }
    Rational(const Rational& rhs) {
        std::cout << "Rational copy constructor." << std::endl;
        this->numerator_ = rhs.numerator_;
        this->denominator_ = rhs.denominator_;
    }
    int numerator() const {
        return numerator_;
    }
    int denominator() const {
        return denominator_;
    }

private:
    int numerator_;
    int denominator_;
};

// RVO 返回值优化
const Rational operator*(const Rational& lhs, const Rational& rhs) {
    Rational tmp(lhs.numerator()*lhs.numerator(), lhs.denominator()*rhs.denominator());
    std::cout << "operator*." << std::endl;
    return tmp;
}

int main() {
    Rational a(1, 2);
    Rational b(3, 4);

    Rational c = a * b;

    return 0;
}

