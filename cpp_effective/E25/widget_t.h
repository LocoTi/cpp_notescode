//
// Created by int.xuqian.zhu on 7/16/2021.
//

// 模板类
#ifndef E25_WIDGET_T_H
#define E25_WIDGET_T_H

#include <iostream>
#include <string>
#include <vector>

namespace WidgetStuff {
    template<typename T>
    class WidgetImpl {
    public:
        explicit WidgetImpl(T i) : i_(i), vec_({}) {}
        T getVal() const {
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
        T i_;
        std::vector<double> vec_;
    };

    template<typename T>
    class Widget {
    public:
        explicit Widget() : impl(nullptr) {}
        ~Widget() {
            delete impl;
        }

        void setImpl(WidgetImpl<T>* val) {
            impl = val;
        }

        Widget& operator=(const Widget &rhs) {
            if (this != &rhs)
                *impl = *(rhs.impl);
            return *this;
        }

        T getVal() const {
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
        WidgetImpl<T>* impl;
    };

    // 由于是模板类，不能偏特化std::swap
    // 所以在class template所在命名空间，添加non-member swap函数
    template<typename T>
    void swap(Widget<T> &a, Widget<T> &b) {
        std::cout << "WidgetStuff swap" << std::endl;
        a.swap(b);
    }
}

#endif //E25_WIDGET_T_H
