#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>

/**
 * 35. 通过 mismatch 或 lexicographical_compare 实现简单的忽略大小写的字符串比较
 */

int ciCharCompare(char c1, char c2) {
    int lc1 = std::tolower(static_cast<unsigned char>(c1));
    int lc2 = std::tolower(static_cast<unsigned char>(c2));

    // 如果为true,要么s1和s2相等，或者s1比s2短
    if (lc1 < lc2) return -1;
    if (lc1 > lc2) return 1;
    return 0;
}

// s1为短的字符串
int ciStringCompareImpl(const std::string &s1, const std::string &s2) {
    typedef std::pair<std::string::const_iterator, std::string::const_iterator> PSCI;
    // [Frist1,Last1) 中的值和[first2,last2)中的元素进行比较，并且返回第一个找到的两个区间中不匹配的值，并且返回
    // PSCI p = std::mismatch(s1.begin(), s1.end(), s2.begin(), std::not2(std::ptr_fun(ciCharCompare)));
    PSCI p = std::mismatch(s1.begin(), s1.end(), s2.begin(), [](char c1, char c2){
        int lc1 = std::tolower(static_cast<unsigned char>(c1));
        int lc2 = std::tolower(static_cast<unsigned char>(c2));

        return (lc1 == lc2);
    });

    // 如果为true,要么s1和s2相等，或者s1比s2短
    if (p.first == s1.end()) {
        if (p.second == s2.end()) return 0;
        else return -1;
    }

    return ciCharCompare(*p.first, *p.second); // 字符串之间的关系和这两个不匹配的字符之间的关系相同
}

int ciStringCompare(const std::string &s1, const std::string &s2) {
    // 把短的字符串作为第一个区间传入
    if (s1.size() <= s2.size())
        return ciStringCompareImpl(s1, s2);
    else
        return -ciStringCompareImpl(s2, s1);
}

// 返回在忽略大小写的情况下，c1是否在c2之前
bool ciCharLess(char c1, char c2) {
    return std::tolower(static_cast<unsigned char>(c1)) <
		std::tolower(static_cast<unsigned char>(c2));
}

bool ciStringCompare2(const std::string& s1, const std::string& s2){
    // 如果[first1, last1)按字典序列小于[first2, last2)，返回true，否则返回false
	return std::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end(), ciCharLess);
}

// C风格 strcmp，ERROR：结果不正确
bool ciStringCompare3(const std::string& s1, const std::string& s2){
	// 前提：不考虑国际化支持，也确定字符串中不会包含内嵌的空字符
    fprintf(stdout, "s1: %s, s2: %s\n", s1.c_str(), s2.c_str());
	return strcmp(s1.c_str(), s2.c_str());
}

void test_item_35() {
    std::string str1{ "xxxz" }, str2{ "xxx" };

    fprintf(stdout, "ciStringCompare str1:str2: %d\n", ciStringCompare(str1, str2));
    fprintf(stdout, "ciStringCompare2 str1:str2: %d\n", ciStringCompare2(str1, str2));
    fprintf(stdout, "ciStringCompare3 str1:str2: %d\n", ciStringCompare3(str1, str2));
}

int main() {
    test_item_35();

    // fprintf(stdout, "%d\n", strcmp("xxx", "yyy"));
    return 0;
}