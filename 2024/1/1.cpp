#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <unordered_map>
#include <vector>

std::vector<int> a, b;

void silver() {
    long long result = 0;
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    for (int i = 0; i < std::ssize(a); ++i) {
        result += std::abs(a[i] - b[i]);
    }
    std::cout << "silver: " << result << std::endl;
}

void gold() {
    std::unordered_map<int, int> counts;
    for (int num : b) {
        ++counts[num];
    }
    long long result = 0;
    for (int num : a) {
        result += num * counts[num];
    }
    std::cout << "gold: " << result << std::endl;
}

int main() {
    int l, r;
    while (std::cin >> l >> r) {
        a.emplace_back(l);
        b.emplace_back(r);
    }
    silver();
    gold();
}