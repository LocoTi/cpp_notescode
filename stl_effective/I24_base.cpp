#include <string>
#include <map>

// 提供提供提供
template<typename MapType, typename KeyArgType, typename ValueArgType>
typename MapType::iterator efficientAddOrUpdate(MapType& m, const KeyArgType& k, const ValueArgType& v) {
    typename MapType::iterator lb = m.lower_bound(k);
    
    if (lb != m.end() && !(m.key_comp()(k, lb->first))) {
        lb->second = v;
        return lb;
    } else {
        typedef typename MapType::value_type MVT;
        return m.insert(lb, MVT(k, v));
    }
}

int test_item_24() {
    std::map<int, std::string> m;
    m[1] = "xxx"; // m[1]是m.operator[](1)的缩写形式
    m.operator[](1) = "xxx";
    
    // m[1] = "xxx"; 在功能上等同于
    typedef std::map<int, std::string> IntStrMap;
    std::pair<IntStrMap::iterator, bool> result = m.insert(IntStrMap::value_type(1, std::string()));
    result.first->second = "yyy";
    
    // 以上方式性能降低的原因：先默认构造了一个string，然后立刻赋给它新的值。如果"直接使用我们所需要的值构造一个
    // string"比"先默认构造一个string再赋值"效率更高，那么，我们最好把对operator[]的使用(包括与之相伴的构造和
    // 赋值)换成对insert的直接调用
	
    m.insert(IntStrMap::value_type(1, "ooo")); // 它通常会节省三个函数调用：一个用于创建默认构造的临时string对象，一个用于析构该临时对象，另一个是调用string的赋值操作符
	
    efficientAddOrUpdate(m, 2, "zzz");
	
    for (auto it = m.begin(); it != m.end(); ++it) {
        fprintf(stdout, "key: %d\t, value: %s\n", it->first, it->second.c_str());
    }
	
    return 0;
}

int main() {
    test_item_24();
}
