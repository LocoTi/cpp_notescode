#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <memory>



/**
 * 33. 对包含指针的容器使用 remove 这一类算法时要特别小心
 */

class Widget33 {
public:
    int mval;
    Widget33(int val): mval(val) { }
	bool isCertified() const { return true; }
};

struct IsCertified {
    bool operator()(Widget33* w) {
        return true;
    }
};
bool isCertified(Widget33*& w) {
    return true;
}

// 如果*pWidget是一个未被验证的Widget33,则删除该指针，并把它置成空
void delAndNullifyUncertified(Widget33*& pWidget)
{
	if (pWidget->isCertified()) {
        std::cout << "delete pWidget." << std::endl;
		delete pWidget;
		pWidget = 0;
	}
}

void test_item_33() {
    std::vector<Widget33*> v;
    Widget33* w1 = new Widget33(1);
    Widget33* w2 = new Widget33(2);
    Widget33* w3 = new Widget33(3);
    Widget33* w4 = new Widget33(4);
    Widget33* w5 = new Widget33(5);
	v.push_back(w1);
	v.push_back(w2);
	v.push_back(w3);
	v.push_back(w4);
	v.push_back(w5);

    // 删除那些指向未被验证过的Widget33对象的指针，会资源泄露
    // v.erase(std::remove_if(v.begin(), v.end(), std::not1(std::mem_fn(&Widget33::isCertified))), v.end());
    v.erase(std::remove_if(v.begin(), v.end(), isCertified), v.end());
    if (w1)
        std::cout << "val: " << w1->mval << std::endl;

    // 一种可以消除资源泄露的做法
	// 将所有指向未被验证的Widget33对象的指针删除并置成空
    v.clear();
    v.push_back(w1);
	v.push_back(w2);
	v.push_back(w3);
	v.push_back(w4);
	v.push_back(w5);
    std::for_each(v.begin(), v.end(), delAndNullifyUncertified);
    // 删除v中的空指针，必须将0转换成一个指针，这样C++才能正确推断出remove的第三个参数类型
    v.erase(std::remove(v.begin(), v.end(), static_cast<Widget33*>(0)), v.end());
    if (w1 != nullptr)
        std::cout << "val: " << w1->mval << std::endl;
    std::cout << "v size: " << v.size() << std::endl;

    // 如果是使用智能指针，则可以直接使用erase_remove_if习惯用法，离开作用域，会自己释放
    std::vector<std::shared_ptr<Widget33>> v2;
    for (int i = 0; i < 5; ++i) v2.push_back(std::make_shared<Widget33>(i));
    // 下面语句需要编译器必须能够把智能指针类型std::shared<Widget33>隐式转换为对应的内置指针类型Widget33*才能通过编译
    // v2.erase(std::remove_if(v2.begin(), v2.end(), std::not1(std::mem_fn(&Widget33::isCertified))), v2.end());
    v2.erase(std::remove_if(v2.begin(), v2.end(), [](std::shared_ptr<Widget33>& ptr){ return true; }), v2.end());
    if (v2[1] != nullptr && v2[1].use_count() > 0)
        std::cout << "val: " << (*v2[1].get()).mval << std::endl;
    
    std::cout << "v2 size: " << v2.size() << std::endl;
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

struct IsOdd {
    bool operator()(const int& x) const {
        return x % 2 == 1;
    }
};

void test_bind() {
    int a[] = {1, 2, 100, 200};

    std::vector< int> arr(a, a + 4);

    // 移除所有小于100的元素 namespace "std" has no member "bind2nd", C++98中的, C++11使用std::bind
    // arr.erase( std::remove_if( arr.begin(),  arr.end(), std::bind2nd( std::less< int>(), 100)), arr.end());

    // std::bind就是std::bind1st和std::bind2nd的加强版
    // 移除所有小于100的元素，less<int>(x, 100)，固定第二个元素
    // arr.erase( std::remove_if( arr.begin(),  arr.end(), std::bind( std::less< int>(), std::placeholders::_1, 100)), arr.end());
    arr.erase( std::remove_if( arr.begin(),  arr.end(), std::bind( [](int a, int b){return (a < b);}, std::placeholders::_1, 100)), arr.end());
    print(arr);

    arr = std::vector<int>(a, a + 4);
    // 移除所有大于100的元素，less<int>(100, x)，固定第一个元素
    // arr.erase( std::remove_if( arr.begin(),  arr.end(), std::bind( std::less< int>(), 100, std::placeholders::_1)), arr.end());
    arr.erase( std::remove_if( arr.begin(),  arr.end(), std::bind( [](int a, int b){return (a < b);}, 100, std::placeholders::_1)), arr.end());
    print(arr);

    arr = std::vector<int>(a, a + 4);
    // 同样实现移除所有大于100的元素，greater<int>(x, 100)，固定第二个元素
    // arr.erase( std::remove_if( arr.begin(),  arr.end(), std::bind( std::greater< int>(), std::placeholders::_1, 100)), arr.end());
    // 或者lambda表达式
    arr.erase( std::remove_if( arr.begin(),  arr.end(), std::bind( [](int a, int b){return (a > b);}, std::placeholders::_1, 100)), arr.end());
    print(arr);

    arr = std::vector<int>(a, a + 4);
    // 移除所有小于等于100的元素，!(x > k) 和 x <= k等价，lambda表达式
    arr.erase( std::remove_if( arr.begin(),  arr.end(), std::bind( [](int a, int b){return !(a > b);}, std::placeholders::_1, 100)), arr.end());
    print(arr);
}

int main() {
    test_item_33();
    test_bind();
}