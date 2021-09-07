#include "stdio.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <time.h>

bool qualityCompare(const int& lhs, const int& rhs)
{
	return (lhs < rhs);
}

bool hasAcceptableQuality(const int& w)
{
	return w % 2 == 0; // 判断w的质量值是否为偶数
}

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

int GetRandomNumber()
{
	int RandomNumber;
	// srand((unsigned)time(NULL));//time()用系统时间初始化种。为rand()生成不同的随机种子。
	RandomNumber = rand() % 15 + 1;//生成1~100随机数
	return RandomNumber;
}

void test_item_31() {
    constexpr int n = 10;
    int ints[n];
    for (int i = 0; i < n; i++)
        ints[i] = GetRandomNumber();
    
    std::vector<int> vints(ints, ints+n);

    // default compare is <
    std::partial_sort(vints.begin(), vints.begin()+5, vints.end());
    // 将质量好的10个元素顺序放在vec的前10个位置上
    std::partial_sort(vints.begin(), vints.begin()+5, vints.end(), qualityCompare);
    print(vints);

    vints.clear();
    vints = std::vector<int>(ints, ints+n);
    // 将最好的10个元素放在vec的前部，但并不关心它们的具体排列顺序
    std::nth_element(vints.begin(), vints.begin()+5, vints.end(), qualityCompare);
    print(vints);

    // std::partia_sort和std::nth_element在效果上唯一不同之处在于：partial_sort对位置1--10中的元素进行了排序，而
	// nth_element没有对它们进行排序。然而，这两个算法都将质量最好的10个vec放到了矢量的前部

    vints.clear();
    vints = std::vector<int>(ints, ints+n);
    std::vector<int>::iterator vbegin(vints.begin());
    std::vector<int>::iterator vend(vints.end());
    std::vector<int>::iterator goalPosition; // 用于定位感兴趣的元素

    // 找到具有中间质量级别的int
    goalPosition = vbegin + vints.size() / 4;
    std::nth_element(vints.begin(), goalPosition, vints.end(), qualityCompare);
    print(vints);

    // 找到区间中具有75%质量的元素
	std::vector<int>::size_type goalOffset = 0.25 * vints.size(); // 找出如果全排序的话，待查找的int离起始处有多远
	std::nth_element(vbegin, vbegin + goalOffset, vend, qualityCompare); // 找到75%处的质量值
    print(vints);

    // 将满足hasAcceptableQuality的所有元素移到前部，然后返回一个迭代器，指向第一个不满足条件的int
	std::vector<int>::iterator goodEnd = std::partition(vints.begin(), vints.end(), hasAcceptableQuality);
    print(vints);
}

int main() {
    test_item_31();
}