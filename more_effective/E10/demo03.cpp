//
// Created by int.xuqian.zhu on 7/28/2021.
//

#include <iostream>
#include <memory>

/**
 * test shared_ptr
 */
class Widget {
public:
    Widget() = default;
    explicit Widget(int id): id_(id) {}
    ~Widget() {
        std::cout << "~Widget()" << std::endl;
    }

    void Print() const {
        std::cout << "id: " << id_ << std::endl;
    }

private:
    int id_;
};

void test_auto_ptr1() {
    // 可能多个auto_ptr指向一个对象，出现重复释放的问题
    std::auto_ptr<Widget> ap1(new Widget);
    std::auto_ptr<Widget> ap2(ap1);  // ok
    std::auto_ptr<Widget> ap3 = ap1;  // ok
}

std::unique_ptr<Widget> getWidget() {
    std::unique_ptr<Widget> up(new Widget(2));
    return up;
}

void test_unique_ptr1() {
    std::unique_ptr<Widget> up1(new Widget(1));
    // unique_ptr不支持拷贝和赋值
//    std::unique_ptr<Widget> ap2(ap1);  // Error
//    std::unique_ptr<Widget> ap3 = ap1;  // Error

    up1->Print();  // 打印id: 1
    // 可以移动构造和移动赋值
    std::unique_ptr<Widget> up2 = getWidget();
    up2->Print();  // 打印id: 2
    std::unique_ptr<Widget> up3 = std::move(up1);  // 这里是显式的所有权转移. 把up1所指的内存转给up3了,而up1不再拥有该内存.
    up3->Print();  // 打印id: 1
    std::unique_ptr<Widget> up4(std::move(up1));
    up4->Print();  // Signal: SIGSEGV (Segmentation fault)
}

int main() {
//    test_auto_ptr1();
    test_unique_ptr1();
}