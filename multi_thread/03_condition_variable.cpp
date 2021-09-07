#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <chrono>

bool ready = false;
std::mutex data_mtx;
std::condition_variable con;

void do_print(int id) {
    std::unique_lock<std::mutex> lck(data_mtx);
    
    std::cout << "Not ready to print id: " << id << std::endl;
    while (!ready) {
        con.wait(lck);
    }
    
    std::cout << "Print the id: " << id << std::endl;
}

void ready_go() {
    std::unique_lock<std::mutex> lck(data_mtx);
    ready = true;
    con.notify_all();
}


int main() {
    constexpr int num = 10;
    std::thread ths[num];
    for (int i = 0; i < num; ++i) {
        ths[i] = std::thread(do_print, i);
    }
    
    std::this_thread::sleep_for(std::chrono::seconds(5));
    
    ready_go();
    for (int i = 0; i < num; ++i) {
        ths[i].join();
    }
    
    return 0;
}
