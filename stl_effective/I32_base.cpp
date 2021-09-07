#include <iostream>
#include <algorithm>
#include <vector>


/**
 * 32. 如果确实需要删除元素，则需要在 remove 这一类算法之后调用 erase
 */

void test_item_32() {
    std::vector<int> v;
    v.reserve(10);
    for (int i = 1; i <= 10; ++i) v.push_back(i);
    fprintf(stdout, "v.size: %d\n", v.size()); // 输出10

    v[3] = v[5] = v[9] = 99;
    for (auto i : v) fprintf(stdout, "%d ", i);
    fprintf(stdout, "\n");

    std::remove(v.begin(), v.end(), 99); // 删除所有值等于99的元素
    fprintf(stdout, "v.size: %d\n", v.size()); // 仍然输出10, remove不是真正意义上的删除，因为它做不到
    for (auto i : v) fprintf(stdout, "%d ", i);
    fprintf(stdout, "\n");

    v.erase(std::remove(v.begin(), v.end(), 99), v.end()); // 真正删除所有值等于99的元素
    for (auto i : v) fprintf(stdout, "%d ", i);
}

int main() {
    test_item_32();
}