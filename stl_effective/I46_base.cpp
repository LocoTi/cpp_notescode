#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <functional>
#include <iterator>

/**
 * 46. 考虑使用函数对象而不是函数作为 STL 算法的参数
 */

struct StringSize {
    std::string::size_type operator()(const std::string& s) {
        return s.size();
    }
};

std::string::size_type stringSize(const std::string& s) {
    return s.size();
}

void test_item_46() {
    std::set<std::string> s{ "abc", "cde", "xyzw" };
    // 普通函数
    std::transform(s.begin(), s.end(), std::ostream_iterator<std::string::size_type>(std::cout, "\n"), stringSize);  // 3 3 4

    std::transform(s.begin(), s.end(), std::ostream_iterator<std::string::size_type>(std::cout, "\n"), std::mem_fn(&std::string::size)); // 3 3 4

    // 函数对象
    std::transform(s.begin(), s.end(), std::ostream_iterator<std::string::size_type>(std::cout, "\n"), StringSize()); // 3 3 4
}

int main() {
    test_item_46();

    return 0;
}