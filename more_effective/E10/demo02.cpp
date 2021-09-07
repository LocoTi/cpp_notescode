//
// Created by int.xuqian.zhu on 7/28/2021.
//

#include <iostream>
#include <memory>

/**
 * test shared_ptr
 */
class Child;
//class Parent {
//public:
//    ~Parent() {
//        std::cout << "~Parent();" << std::endl;
//    }
//
//    std::shared_ptr<Child> ptr_;
//};
//class Child {
//public:
//    ~Child() {
//        std::cout << "~Child();" << std::endl;
//    }
//
//    std::shared_ptr<Parent> ptr_;
//
//};

//void test_shared_ptr1() {
//    std::shared_ptr<Parent> p(new Parent);
//    std::shared_ptr<Child> c(new Child);
//
//    p->ptr_ = c;
//    c->ptr_ = p;
//
//    // 退出作用域，p和c两个shared_ptr并没有被释放，造成循环引用
//    std::cout << "quit scope." << std::endl;
//}


/**
 * test weak_ptr
 */
class Parent {
public:
    ~Parent() {
        std::cout << "~Parent();" << std::endl;
    }

    std::shared_ptr<Child> ptr_;
};
class Child {
public:
    ~Child() {
        std::cout << "~Child();" << std::endl;
    }

    std::weak_ptr<Parent> ptr_;

};

void test_shared_ptr2() {
    std::shared_ptr<Parent> p(new Parent);
    std::shared_ptr<Child> c(new Child);

    p->ptr_ = c;
    c->ptr_ = p;

    // 使用weak_ptr可以解决循环引用问题
    std::cout << "quit scope." << std::endl;
}
int main() {
//    test_shared_ptr1();
    test_shared_ptr2();
}

