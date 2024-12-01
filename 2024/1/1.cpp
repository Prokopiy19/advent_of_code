#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <vector>

int main() {
    std::vector<int> l, r;
    int x, y;
    while (std::cin >> x >> y) {
        l.emplace_back(x);
        r.emplace_back(y);
    }

    long long silver = 0;
    std::sort(l.begin(), l.end());
    std::sort(r.begin(), r.end());
    for (int i = 0; i < std::ssize(l); ++i) {
        silver += std::abs(l[i] - r[i]);
    }
    std::cout << "silver: " << silver << std::endl;

    long long gold = 0;
    auto lit = l.cbegin();
    auto rit = r.cbegin();
    while (lit != l.cend() && rit != r.cend()) {
        while (rit != r.cend() && *lit > *rit) {
            ++rit;
        }
        const auto rit0 = rit;
        while (rit != r.cend() && *lit == *rit) {
            ++rit;
        }
        const auto lit0 = lit;
        while (lit != l.cend() && *lit == *lit0) {
            ++lit;
        }
        gold += *lit0 * (lit - lit0) * (rit - rit0);
    }
    std::cout << "gold: " << gold << std::endl;
}