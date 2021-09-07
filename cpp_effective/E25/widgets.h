//
// Created by int.xuqian.zhu on 7/16/2021.
//

// 普通类
#ifndef WIDGET_H
#define WIDGET_H

#include <iostream>
#include <string>
#include <vector>

class WidgetImpl {
public:
    explicit WidgetImpl(int i) : i_(i), vec_({}) {}
    int getVal() const {
        return i_;
    }

    void setVec(const std::vector<double> &val) {
        vec_ = val;
    }

    void print() {
        for (double item : vec_) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }

private:
    int i_;
    std::vector<double> vec_;
};

class Widget {
public:
    explicit Widget() : impl(nullptr) {}
    ~Widget() {
        delete impl;
    }

    void setImpl(WidgetImpl* val) {
        impl = val;
    }

    Widget& operator=(const Widget &rhs) {
        if (this != &rhs)
            *impl = *(rhs.impl);
        return *this;
    }

    int getVal() {
        return this->impl->getVal();
    }

    void swap(Widget &rhs) {
        using std::swap;
        swap(impl, rhs.impl);
    }

    void print() {
        impl->print();
    }
private:
    WidgetImpl* impl;
};

// 普通类，全特化std的swap
namespace std {
    template<>
    void swap<Widget>(Widget &a, Widget &b) {
        std::cout << "std specialized." << std::endl;
        a.swap(b);
    }
}

#endif // WIDGET_H