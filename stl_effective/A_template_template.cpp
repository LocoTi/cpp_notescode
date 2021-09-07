#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <set>

// template<typename Container>
// void print(Container C) {
//     typedef typename iterator_traits<typename Container::iterator>::value_type ValType;
//     if (!C.empty()) {
//         typename Container::const_iterator it = C.cbegin();
//         while (it != C.cend()) {
//             std::cout << *it++ << " ";
//         }
//         std::cout << std::endl;
//     }
// }

template<typename T, template<class> class Container>
class Printer {
private:
    Container<T> c_;
public:
    void operator()(const Container<T> &c) {
        if (!c.empty()) {
            typename Container<T>::const_iterator it = c.cbegin();
            while (it != c.cend()) {
                std::cout << *it++ << " ";
            }
            std::cout << std::endl;
        }
    }
};

template<typename T>
using Vec = std::vector<T, std::allocator<T>>;

template<typename T>
using Lst = std::list<T, std::allocator<T>>;

void test() {
    std::vector<int> c1{1, 41, 25, 26, 1983, 1983, 87};
    Printer<int, Vec> printerVec;
    printerVec(c1);

    Vec<int> c2{1, 41, 25, 26, 1983, 1983, 87};
    printerVec(c2);

    Lst<int> c3{3, 5, 67, 99, 1983, 98, 80};
    Printer<int, Lst> printerLst;
    printerLst(c3);
}

int main() {
    test();
}