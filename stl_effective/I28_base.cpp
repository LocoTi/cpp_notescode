#include <stdio.h>
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

int test_item_28() {
    std::vector<int> v;
    v.reserve(5);
    
    for (int i = 1; i <= 5; ++i)
        v.push_back(i);
    
    std::vector<int>::reverse_iterator ri = std::find(v.rbegin(), v.rend(), 3); // ri -> 3
    std::vector<int>::iterator i(ri.base());
    fprintf(stdout, "%d\n", (*i)); // 4
    v.insert(i, 99);
    
    for (auto it = v.cbegin(); it != v.cend(); ++it)
        fprintf(stdout, "value: %d\n", *it);     // 1 2 3 99 4 5
    
    v.clear();
    v.reserve(5);
    for (int i = 1; i <= 5; ++i)
        v.push_back(i);
    
    ri = std::find(v.rbegin(), v.rend(), 3);
    v.erase((++ri).base());
    for (auto it = v.cbegin(); it != v.cend(); ++it)
        fprintf(stdout, "value: %d\n", *it);     // 1 2 4 5
    
    return 0;
}

int main() {
    test_item_28();
}