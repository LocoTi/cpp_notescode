//
// Created by int.xuqian.zhu on 8/3/2021.
//

#include <iostream>
#include <vector>

#define HISTO_LENGTH 30

int main() {
    std::vector<int> rotHist[HISTO_LENGTH];
    for(int i=0;i<HISTO_LENGTH;i++)
        rotHist[i].reserve(500);

    for(int i=0;i<HISTO_LENGTH;i++)
        std::cout << rotHist[i].size() << " ";
    return 0;
}