#include <charconv>
#include <iostream>
#include <string>
#include <unordered_map>

std::array<std::unordered_map<unsigned long long, unsigned long long>, 76> memo{};

unsigned long long dfs(unsigned long long num, int i) {
    if (i == 0) {
        return 1;
    }
    if (memo[i].contains(num)) {
        return memo[i][num];
    }
    if (num == 0) {
        return memo[i][num] = dfs(1, i - 1);
    } else if (auto s = std::to_string(num); s.size() % 2 == 0) {
        auto new_len = s.size() / 2;
        unsigned long long lhs;
        unsigned long long rhs;
        std::from_chars(s.c_str(), s.c_str() + new_len, lhs);
        std::from_chars(s.c_str() + new_len, s.c_str() + s.size(), rhs);
        return memo[i][num] = dfs(lhs, i - 1) + dfs(rhs, i - 1);
    }
    return memo[i][num] = dfs(num * 2024, i - 1);
}

int main() {
    unsigned long long silver = 0;
    unsigned long long gold = 0;
    for (unsigned long long num; std::cin >> num; ) {
        silver += dfs(num, 25);
        gold += dfs(num, 75);
    }
    std::cout << "silver: " << silver << '\n';
    std::cout << "gold:   " << gold << '\n';
}