#include <iostream>
#include <vector>

class Element
{
public:
    Element(int i) : i_(i), c_({}) { } 

    void setVec(const std::vector<double> &c) {
        c_ = c;
    }

    void print() {
        std::cout << "Element " << i_ << " elements:\n";
        for (double item : c_) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
private:
    int i_;
    std::vector<double> c_;
};

class Sample
{
private:
    Element* p;

public:
    ~Sample() {
        delete p;
        p = nullptr;
    };
    Sample(): p(nullptr) { }
    Sample(const Sample& rhs)
    {
        std::cout << "copy constructor." << std::endl;
        memcpy(p, rhs.p, sizeof(Element));
    }

    Sample& operator= (const Sample& s)
    {
        std::cout << "copy assign operator." << std::endl;
        if(this != &s)
        {
            Sample temp(s);
            // swap(*this, temp); // ERROR
            
            // Element *e = temp.p;
            // temp.p = p;
            // p = e;
            this->swap(temp);
        }
        return *this;
    }
    
    void swap(Sample& s)
    {
        using std::swap;
        std::swap(p, s.p);
    }

    void set(Element* p_ele) {
        p = p_ele;
    }

    void print() {
        p->print();
    }
};

namespace std
{
    template<>
    void swap<Sample>(Sample &s1, Sample &s2)
    {
        std::cout << "std specialized." << std::endl;
        s1.swap(s2); // 在这里调用类的成员函数
    }
}

int main() {
    Element* e1 = new Element(1);
    e1->setVec({1, 2, 3});
    Sample s1;
    s1.set(e1);

    Element* e2 = new Element(2);
    e2->setVec({4, 5, 6});
    Sample s2;
    s2.set(e2);

    s1.print();
    s2.print();

    std::cout << "======================= swap =====================" << std::endl;

    std::swap(s1, s2);
    s1.print();
    s2.print();

    std::cout << "======================= assgin =====================" << std::endl;

    Element* e3 = new Element(3);
    e3->setVec({7, 8, 9});
    Sample s3;
    s3.set(e3);

    s3.print();

    s2 = s3;
    s2.print();
    s3.print();

    return 0;
}