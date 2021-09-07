//
// Created by int.xuqian.zhu on 7/27/2021.
//

#include <iostream>
#include <new>
#include <string>

class Widget8 {
public:
    Widget8(int widgetSize) {}
};

void* mallocShared(size_t size) {
    return operator new(size);
}

void freeShared(void* memory) {
    operator delete(memory);
}

Widget8* constructWidget8InBuffer(void* buffer, int widget8Size) {
    return new (buffer) Widget8(widget8Size);  // placement new 操作符需要而外提供一个参数buffer，new内部调用operator new函数时会传入这个参数
    // 被调用的operator new除了上述的一个size_t参数外，还必须指定一个void*参数，指向构造造出来的对象。这个operator new就是placement new
    // void* operator new(size_t size, void* location) { return location; }
}

int test_item_8() {
    std::string* ps = new std::string("Memory Management");  // 使用new调用new操作符(new operator)
    // void* operator(size_t size)  // 函数operator new通常声明
    void* rawMemory = operator new(sizeof(std::string));  // 操作符operator new将返回一个指针，指向一块足够容纳一个string类型对象的内存
    operator delete(rawMemory);

    delete ps;  // 1.ps->~std::string(); 2.operator delete(ps);

    void* buffer = operator new(50 * sizeof(char));  // 分配足够的内存以容纳50个char，没有调用构造函数
    operator delete(buffer);  // 释放内存，没有调用析构函数. 这与在C中调用malloc和free等同OA

    void* sharedMemory = mallocShared(sizeof(Widget8));
    Widget8* pw = constructWidget8InBuffer(sharedMemory, 10);  // placement new
    // delete pw;  // 错误，非operator new，不能直接delete

    // placement new出来的对象，需要分两步删除
    pw->~Widget8();  // 正确，析构pw指向的Widget8,但是没有释放包含Widget8的内存
    freeShared(sharedMemory);  //  正确，释放pw指向的共享内存，但是没有调用析构函数

    return 0;
}

int main() {
    test_item_8();
}