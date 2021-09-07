#include <iostream>
#include <deque>

void test_item_27() {
    typedef std::deque<int> IntDeque;
    typedef IntDeque::iterator Iter;
    typedef IntDeque::const_iterator ConstIter;
    
    IntDeque d{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    ConstIter cit;
    cit = d.cbegin() + 1;
    std::cout << "cit value: " << *cit << std::endl;
    
    Iter it(d.begin());
    std::cout << "it value: " << *it << std::endl;
    
    std::cout << "the distance between it and cit: " << std::distance<ConstIter>(it, cit) << std::endl;
    std::advance(it, std::distance<ConstIter>(it, cit));
    
    std::cout << "cit after advance value: " << *cit << std::endl;
}

int main() {
    test_item_27();
}
