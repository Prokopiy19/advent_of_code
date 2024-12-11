#include <array>
#include <iostream>
#include <unordered_map>

std::array<std::unordered_map<unsigned long long, unsigned long long>, 76> memo{};

int countDigits(unsigned long long num) {
    int ret = 0;
    do {
        ++ret;
        num /= 10;
    } while (num);
    return ret;
}

unsigned long long dfs(unsigned long long num, int i) {
    if (i == 0) {
        return 1;
    }
    if (auto it = memo[i].find(num); it != memo[i].end()) {
        return it->second;
    }
    if (num == 0) {
        return memo[i][num] = dfs(1, i - 1);
    } else if (int n = countDigits(num); n % 2 == 0) {
        unsigned long long p10 = 1;
        unsigned long long x = 10;
        n /= 2;
        while (n) {
            if (n % 2) {
                p10 *= x;
            }
            x *= x;
            n /= 2;
        }
        return memo[i][num] = dfs(num / p10, i - 1) + dfs(num % p10, i - 1);
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