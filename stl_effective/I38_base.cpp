#include <iostream>
#include <algorithm>


class Widget38 {};
template<typename T> class BPFC;

template<typename T>
class BPFCImpl {
public:
    BPFCImpl(const Widget38& w, int x): mw(w), mx(x) { }
    virtual ~BPFCImpl() {}; // 多态类需要虚析构函数
private:
    Widget38 mw; // 原来BPFC中所有数据现在都放在这里
    int mx;
    virtual void operator()(const T& val) const {
        std::cout << "base BPFCImpl: " << val << "\n";
    };

    friend class BPFC<T>; // 允许BPFC访问内部数据
};

template<typename T>
class SubBPFCImpl : public BPFCImpl<T> {
public:
    SubBPFCImpl(const Widget38& w, int x): BPFCImpl<T>(w, x) { }
    ~SubBPFCImpl() {}
private:
    void operator()(const T& val) const {
        std::cout << "derived BPFCImpl: " << val << "\n";
    }
};

template<typename T>
class BPFC {
private:
    BPFCImpl<T>* pImpl; // BPFC唯一的数据成员
public:
    BPFC(BPFCImpl<T>* p) : pImpl(p) { }
    void operator()(const T& val) const {  // 现在这是一个非虚函数，将调用转到BPFCImpl中
        pImpl->operator()(val);
    }
};

void test_item_38() {
    Widget38 w;
    int x = 0;
    BPFCImpl<int>* bpfcImpl = new SubBPFCImpl<int>(w, x);
    BPFC<int> bpfc(bpfcImpl);

    int val = 10;
    bpfc(val);
}

int main() {
    test_item_38();
}