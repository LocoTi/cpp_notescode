#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <set>
#include <algorithm>

bool badValue(int) {
    return true;  // 返回x是否是坏值
}

template<typename Container>
void print(const Container &C, std::ostream &os) {
    if (!C.empty()) {
        typename Container::const_iterator it = C.cbegin();
        while (it != C.cend()) {
            os << *it++ << " ";
        }
        os << std::endl;
    }
}

int test_item_9() {
    
    std::vector<int> c1{1, 4, 23, 1963, 1964, 1963, 224};
    // 当c1是vector, string或deque时，erase-remove习惯用法是删除特定值的元素的最好办法
    // 因为remove只是将需要删除的值移动到后方，没有真正删除
    c1.erase(std::remove(c1.begin(), c1.end(), 1963), c1.end());
    print(c1, std::cout);

    std::list<int> c2{1, 4, 23, 1963, 1964, 1963, 224};
    // 当c2是list时，remove成员函数是删除特定值的元素的最好办法
    c2.remove(1963);
    print(c2, std::cout);

    std::set<int> c3{1, 4, 23, 1963, 1964, 1963, 224};
	c3.erase(1963); // 当c3是标准关联容器时，erase成员函数是删除特定值元素的最好办法
    print(c3, std::cout);

    // 删除判别式(predicate)返回true的每一个对象
	c1.erase(std::remove_if(c1.begin(), c1.end(), badValue), c1.end()); // 当c1是vector, string或deque时，这是删除使badValue返回true的对象的最好办法
    print(c1, std::cout);

    c2.remove_if(badValue); // 当c2是list时，这是删除使badValue返回true的对象的最好办法
    print(c2, std::cout);

    for (std::set<int>::iterator i = c3.begin(); i != c3.end();) {
        if (badValue(*i))
            c3.erase(i++);  // 对坏值，把当前的i传给erase，递增i是副作用
        else
            ++i;            // 对好值，则简单的递增i
    }
    print(c3, std::cout);

    // 每次元素被删除时，都向一个日志(log)文件中写一条信息
	std::ofstream logFile("logfile.log");
	for (std::set<int>::iterator i = c3.begin(); i != c3.end();) {
		if (badValue(*i)) {
			logFile << "Erasing " << *i << '\n'; // 写日志文件
			c3.erase(i++); // 对坏值，把当前的i传给erase，递增i是副作用
		}
		else ++i;              // 对好值，则简单第递增i
	}
 
	for (std::vector<int>::iterator i = c1.begin(); i != c1.end();) {
		if (badValue(*i)) {
			logFile << "Erasing " << *i << '\n';
			i = c1.erase(i); // 把erase的返回值赋给i，使i的值保持有效
		}
		else ++i;
	}
 
	return 0;
}

int main() {
    test_item_9();
}