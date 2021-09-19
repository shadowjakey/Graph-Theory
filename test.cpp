#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>

using std::cout;
using std::endl;
using std::vector;
using std::unordered_map;

int main() {
    unordered_map<std::string, int> urmom;
    urmom["hello"] = 69;
    urmom["bye"] = 23;
    urmom["urmom"] = 64;
    urmom["a"] = 965;
    urmom["e"] = 45;
    for(auto i : urmom) {
        cout << i.first << endl;
    }

    return 0;
}