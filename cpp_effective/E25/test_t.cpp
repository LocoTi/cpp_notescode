//
// Created by int.xuqian.zhu on 7/16/2021.
//

#include "widget_t.h"
using namespace WidgetStuff;

int main(int argc, char **argv) {
    WidgetImpl<double>* i1 = new WidgetImpl<double>(1.5);
    i1->setVec(std::vector<double>({1.0, 2.0, 3.0}));
    Widget<double> w1;
    w1.setImpl(i1);

    WidgetImpl<double>* i2 = new WidgetImpl<double>(2.5);
    i2->setVec(std::vector<double>({4.0, 5.0, 6.0}));
    Widget<double> w2;
    w2.setImpl(i2);

    std::cout.precision(3);
    std::cout << "w1 val: " << w1.getVal() << std::endl;
    w1.print();
    std::cout << "w2 val: " << w2.getVal() << std::endl;
    w2.print();

    std::cout << "======================= swap =====================" << std::endl;

    swap(w1, w2);

    std::cout << "w1 val: " << w1.getVal() << std::endl;
    w1.print();
    std::cout << "w2 val: " << w2.getVal() << std::endl;
    w2.print();

    return 0;
}