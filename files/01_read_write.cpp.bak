#include <fstream>
#include <iostream>
#include <string>

int main() {
    std::ofstream os;
    os.open("test_files.data");
    
    std::string str;
    while (1) {
        std::cin >> str;
	if (str == "q")
            break;
	os << str << "\n";
    }

    os.close();

    std::ifstream is("test_files.data");
    if (!is.is_open()) {
        std::cerr << "open file failed!" << std::endl;
    }
    std::cout << "start reading file..." << std::endl;
    
    char data[1024];
    while (!is.eof()) {
        is.getline(data, 1024);
	    std::cout << data << std::endl;
    }

    return 0;
}
