#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>

/**
 * 41. 理解 ptr_fun**、men_fun** 和 mem_fun_ref 的来由
 */

class Widget41 {
public:
    Widget41(int id): mid(id) { }
	void test() {
        fprintf(stdout, "Widget41 id: %d\n", mid);
    }
    int mid;
};
 
void test(Widget41& w) {
    fprintf(stdout, "Widget41 id: %d\n", w.mid);
}

void test_item_41() {
    std::vector<Widget41> vw;
    vw.emplace_back(Widget41(1));
    vw.emplace_back(Widget41(2));
    vw.emplace_back(Widget41(3));
    vw.emplace_back(Widget41(4));
    vw.emplace_back(Widget41(5));
    
    std::for_each(vw.begin(), vw.end(), test);
    // std::for_each(vw.begin(), vw.end(), std::ptr_fun(test));
    // std::for_each(vw.begin(), vw.end(), &Widget41::test);
    std::for_each(vw.begin(), vw.end(), std::mem_fn(&Widget41::test));

    std::list<Widget41*> lpw;
    std::for_each(lpw.begin(), lpw.end(), std::mem_fn(&Widget41::test));
}

int main() {
    test_item_41();

    return 0;
}