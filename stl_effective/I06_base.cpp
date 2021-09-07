#include <fstream>
#include <iostream>
#include <list>
#include <iterator>

// 注意：围绕参数名的括号(比如对f2中d)与独立的括号的区别：围绕参数名的括号被忽略，而独立的括号则表明参数
// 列表的存在：它们说明存在一个函数指针参数
int f1(double d); // 声明了一个带double参数并返回int的函数
int f2(double(d)); // 同上，d两边的括号被忽略,可以给参数名加上圆括号
int f3(double); // 同上，参数名被忽略
 
int g1(double(*pf)()); // 参数是一个指向不带任何参数的函数的指针，该函数返回double值；g1以指向函数的指针为参数
int g2(double pf()); // 同上，pf为隐式指针
int g3(double()); // 同上，省去参数名

int test_item_6() {
	// 把一个存有整数(int)的文件ints.dat拷贝到一个list中
	std::ifstream dataFile("ints.data");
	if (!dataFile.is_open()) {
		std::cerr << "open file failed!" << std::endl;
	}
	
	std::list<int> data1(std::istream_iterator<int>(dataFile), std::istream_iterator<int>()); // 小心，结果不会是你所想象的那样
	
// 	for (std::list<int>::iterator it=data1.begin(); it != data1.end(); ++it) {
// 		std::cout << *it << " ";
// 	}

// 	std::list<int> data2((std::istream_iterator<int>(dataFile)), std::istream_iterator<int>()); // 正确，注意list构造函数的第一个参数两边的括号

// 	std::cout << "data2: " << std::endl;
// 	for (std::list<int>::iterator it=data2.begin(); it != data2.end(); ++it) {
//   		std::cout << *it << " ";
//   	}

	std::istream_iterator<int> dataBegin(dataFile);
	std::istream_iterator<int> dataEnd;
	std::list<int> data3((dataBegin), dataEnd); // 正确

	std::cout << "data3: " << std::endl;
  	for (std::list<int>::iterator it=data3.begin(); it != data3.end(); ++it) {
  		std::cout << *it << " ";
  	}

	return 0;
}

int main() {
    test_item_6();
}