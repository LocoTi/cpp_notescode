#include "stdio.h"
#include <functional>
#include <string>
#include <vector>
#include <set>

struct StringPtrLess: public std::binary_function<const std::string*, const std::string*, bool> {
    bool operator()(const std::string* ps1, const std::string* ps2) const {
        return *ps1 < *ps2;
    }
};

struct DereferenceLess {
    template<typename PtrType>
    bool operator()(PtrType pT1, PtrType pT2) const {
        return *pT1 < *pT2;
    }
};

int test_item_20() {
    std::set<std::string*> dssp;  // std::set<std::string*> <==> std::set<std::string*, std::less<std::string*>>, 得不到预期的效果
    dssp.insert(new std::string("Anteater"));
    dssp.insert(new std::string("Wombat"));
    dssp.insert(new std::string("Lemur"));
    dssp.insert(new std::string("Penguin"));
    
    for (auto it = dssp.begin(); it != dssp.end(); ++it) {
        fprintf(stdout, "%s\n", (**it).c_str());
    }

    // std::<std::string*, StringPtrLess> ssp;
    std::set<std::string*, DereferenceLess> ssp; // 与std::set<std::string*, StringPtrLess> ssp;的行为相同
    ssp.insert(new std::string("Anteater"));
    ssp.insert(new std::string("Wombat"));
    ssp.insert(new std::string("Lemur"));
    ssp.insert(new std::string("Penguin"));

    for (auto it = ssp.begin(); it != ssp.end(); ++it) {
        fprintf(stdout, "%s\n", (**it).c_str());
    }

    return 0;
}

int main() {
    test_item_20();
}
