//
// Created by int.xuqian.zhu on 7/28/2021.
//

#include <iostream>
#include "cstring"

// 同样char *c = "abc"和char c[]="abc", 前者改变其内容程序是会崩溃的，而后者完全正确
void test_exception1() {
    char c0[] = {'1', '2', '3'};
    c0[0] = '3';

    char *c1 = "abc";  // "abc"在常量区，编译器分配
    char c2[] = "abc";  // "abc"在栈上，运行时分配
    c2[0] = 'b';

    char *c3 = (char*) malloc(sizeof(char));
    c3 = "abc";  // c3和c1 地址相同
    // c3[0] = 'b';  // 通过c3 = "abc", ERROR

//    strcpy(c3,"abc");  // c3和c1地址不同，但是"abc"和c1所指"abc"是同一个字符串常量
//    c3[0] = 'b';  // strcpy(c3,"abc"), OK

    printf("%p, %p, %s\n", &c1, c1, c1);
    printf("%p, %p, %s\n", &c2, c2, c2);
    printf("%p, %p, %s\n", &c3, c3, c3);
}

int main() {
    test_exception1();
}