#include <stdio.h>
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <list>

int transmogrify(int x) {
	return (x + 1);
}

int test_item_30() {
    std::vector<int> values{1, 2, 3};
	std::vector<int> results;

	results.reserve(results.size() + values.size());  // reserve避免内存重新分配
	std::transform(values.cbegin(), values.cend(), results.end(), transmogrify);  // 错误，segmentation fault
    std::transform(values.cbegin(), values.cend(), std::back_inserter(results), transmogrify);  // 正确
	// 在内部，std::back_inserter返回的迭代器将使得push_back被调用，所以back_inserter可适用于所有提供了push_back方法的容器
	
	std::list<int> results2;
	std::transform(values.cbegin(), values.cend(), std::front_inserter(results2), transmogrify);
	// std::front_inserter在内部利用了push_front，所以front_inserter仅适用于那些提供了push_front成员函数的容器
	
	for (auto it = results2.begin(); it != results2.end(); ++it) {
		std::cout << *it << " ";
	}
	return 0;
}

int main() {
    test_item_30();
}