#include <iostream>
#include <algorithm>
#include <vector>

template<typename Container>
void print(Container C) {
    // typedef typename iterator_traits<typename Container::iterator>::value_type ValType;
    if (!C.empty()) {
        typename Container::const_iterator it = C.cbegin();
        while (it != C.cend()) {
            std::cout << *it++ << " ";
        }
        std::cout << std::endl;
    }
}

struct cmp {
    bool operator()(int a, int b) {
        return a > b;
    }
};

void test_lower_upper_bound() {
    int lesses[10] = {2, 4, 5, 8, 9, 11, 14, 15, 20, 24};

    fprintf(stdout, "===============less vector=================\n");
    std::vector<int> vlesses(lesses, lesses+10);
    print(vlesses);

    // lower_bound 和 upper_bound默认容器是从小到大排序
    // lower_bound：在容器中查找大于等于指定元素值的第一个元素所在位置，相当于找到查找值所在位置的前插入位置
    std::vector<int>::iterator pos = std::lower_bound(vlesses.begin(), vlesses.end(), 8);
    fprintf(stdout, "lower_bound value pos: %d\n", std::distance(vlesses.begin(), pos));
    vlesses.insert(pos, 9);
    print(vlesses);

    sort(vlesses.begin(), vlesses.end());
    print(vlesses);

    // upper_bound：在容器中查找大于指定元素值的第一个元素所在位置，相当于找到查找值所在位置的后插入位置
    pos = std::upper_bound(vlesses.begin(), vlesses.end(), 8);
    fprintf(stdout, "upper_bound value pos: %d\n", std::distance(vlesses.begin(), pos));
    vlesses.insert(pos, 10);
    print(vlesses);

    fprintf(stdout, "===============greater vector=================\n");
    std::vector<int> vgreaters(lesses, lesses+10);
    sort(vgreaters.begin(), vgreaters.end(), cmp());
    print(vgreaters);

    // 如果容器是从大到小排序，则需要加入比较器
    pos = std::lower_bound(vgreaters.begin(), vgreaters.end(), 8, std::greater<int>());
    fprintf(stdout, "lower_bound value pos: %d\n", std::distance(vgreaters.begin(), pos));
    vgreaters.insert(pos, 9);
    print(vgreaters);
}

int main() {
    test_lower_upper_bound();

    return 0;
}