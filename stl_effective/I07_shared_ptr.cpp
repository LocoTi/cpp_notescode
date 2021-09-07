// vector assign
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

#include <thread>
#include <chrono>
#include <mutex>

class Widget7 {
public:
    ~Widget7() {
        std::cout << "Widget7 deconstructor." << std::endl;
    }
};

struct DeleteObj {
    template<typename T>
    void operator()(T *ptr){
        delete ptr;
    }
};

int test_item_15()
{
	fprintf(stdout, "string size: %d, char* size: %d\n", sizeof(std::string), sizeof(char*));
 
	return 0;
}


struct Base
{
	Base() { std::cout << "  Base::Base()\n"; }
	// Note: non-virtual destructor is OK here
	~Base() { std::cout << "  Base::~Base()\n"; }
};
 
struct Derived : public Base
{
	Derived() { std::cout << "  Derived::Derived()\n"; }
	~Derived() { std::cout << "  Derived::~Derived()\n"; }
};
 
void thr(std::shared_ptr<Base> p)
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::shared_ptr<Base> lp = p; // thread-safe, even though the shared use_count is incremented
	{
		static std::mutex io_mutex;
		std::lock_guard<std::mutex> lk(io_mutex);
		std::cout << "local pointer in a thread:\n"
			<< "  lp.get() = " << lp.get()
			<< ", lp.use_count() = " << lp.use_count() << '\n';
	}
}
 
int test_shared_ptr1()
{
	std::shared_ptr<Base> p = std::make_shared<Derived>();
 
	std::cout << "Created a shared Derived (as a pointer to Base)\n"
		<< "  p.get() = " << p.get()
		<< ", p.use_count() = " << p.use_count() << '\n';
	std::thread t1(thr, p), t2(thr, p), t3(thr, p);
	p.reset(); // release ownership from main
	std::cout << "Shared ownership between 3 threads and released\n"
		<< "ownership from main:\n"
		<< "  p.get() = " << p.get()
		<< ", p.use_count() = " << p.use_count() << '\n';
	t1.join(); t2.join(); t3.join();
	std::cout << "All threads completed, the last one deleted Derived\n";
 
	return 0;
}
 
///
// reference: http://www.cplusplus.com/reference/memory/shared_ptr/shared_ptr/
int test_shared_ptr2()
{
	struct C { int* data; };
 
	// shared_ptr constructor example
	std::shared_ptr<int> p1;
	std::shared_ptr<int> p2(nullptr);
	std::shared_ptr<int> p3(new int);
	std::shared_ptr<int> p4(new int, std::default_delete<int>());
	std::shared_ptr<int> p5(new int, [](int* p){delete p; }, std::allocator<int>());
	std::shared_ptr<int> p6(p5);
	std::shared_ptr<int> p7(std::move(p6));
	std::shared_ptr<int> p8(std::unique_ptr<int>(new int));
	std::shared_ptr<C> obj(new C);
	std::shared_ptr<int> p9(obj, obj->data);
 
	std::cout << "use_count:\n";
	std::cout << "p1: " << p1.use_count() << '\n'; // 0
	std::cout << "p2: " << p2.use_count() << '\n'; // 0
	std::cout << "p3: " << p3.use_count() << '\n'; // 1
	std::cout << "p4: " << p4.use_count() << '\n'; // 1
	std::cout << "p5: " << p5.use_count() << '\n'; // 2
	std::cout << "p6: " << p6.use_count() << '\n'; // 0
	std::cout << "p7: " << p7.use_count() << '\n'; // 2
	std::cout << "p8: " << p8.use_count() << '\n'; // 1
	std::cout << "p9: " << p9.use_count() << '\n'; // 2
 
	return 0;
}

int main ()
{
    std::vector<Widget7 *> vpw1, vpw2;
    const int num = 3;
    
    for (int i = 0; i < num; ++i) {
        vpw1.push_back(new Widget7);
        vpw2.push_back(new Widget7);
    }
    
    for (std::vector<Widget7 *>::iterator it = vpw1.begin(); it != vpw1.end(); ++it) {
        delete *it;
    }
    
    for_each(vpw2.begin(), vpw2.end(), DeleteObj());
    
    typedef std::shared_ptr<Widget7> SPW;
    std::vector<SPW> vpw3;
    for (int i = 0; i < num; ++i) {
        vpw3.push_back(SPW(new Widget7));
    }
    
    test_item_15();
    test_shared_ptr1();
    test_shared_ptr2();
    
    return 0;
}
