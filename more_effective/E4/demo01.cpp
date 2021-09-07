//
// Created by int.xuqian.zhu on 7/27/2021.
//

/**
* 4. 避免无用的缺省构造函数
*/

#include <iostream>
#include <new>

class EquipmentPiece {
public:
    EquipmentPiece(int IDNumber) {}  // 提供了单参数构造函数，没有默认构造函数
};

int test_item_4() {
//    EquipmentPiece bestPieces[10];  // 错误，没有正确调用EquipmentPiece构造函数
//    EquipmentPiece *bestPieces2 = new EquipmentPiece[10];  // 错误，没有正确调用EquipmentPiece构造函数

    int ID1 = 1, ID2 = 2;
    EquipmentPiece bestPieces3[] = {EquipmentPiece(ID1), EquipmentPiece(ID2)};  // 正确，调用了单参数构造函数

    // 利用指针数组代替一个对象数组
    typedef EquipmentPiece* PEP;  // PEP指针指向一个EquipmentPiece对象
    PEP bestPieces4[10];  // 正确，没有调用构造函数
    PEP* bestPieces5 = new PEP[10]; // 也正确

    // 在指针数组里的每一个指针被重新赋值，以指向一个不同的EquipmentPiece对象
    for (int i = 0; i < 10; ++i) {
        bestPieces5[i] = new EquipmentPiece(i);
    }

    // 为数组分配raw memory，避免浪费内存，placement new方法在内存中构造EquipmentPiece对象
    void* rawMemory = operator new[](10 * sizeof(EquipmentPiece));
    // rawMemory转为EquipmentPiece array，并让bestPieces6指向指向它
    EquipmentPiece* bestPieces6 = static_cast<EquipmentPiece*>(rawMemory);
    // 构造bestPieces6中每个元素，使用placement new
    for (int i = 0; i < 10; ++i) {
        new(&bestPieces6[i]) EquipmentPiece(i);
    }
    // 与构造函数bestPieces6对象相反的顺序析构
    for (int i = 9; i >= 0; --i) {
        bestPieces6[i].~EquipmentPiece();  // 如果使用普通的数组删除方法，程序的运行是不可预测的
    }

    // deallocate the raw memory
    delete [] rawMemory;

    return 0;
}

int main() {
    test_item_4();
}