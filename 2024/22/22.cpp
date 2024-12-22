#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

int nextSecret(long long num) {
    num = (num ^ (num << 6)) & 16777215;
    num = (num ^ (num >> 5)) & 16777215;
    num = (num ^ (num << 11)) & 16777215;
    return num;
}

int hashArray(std::array<std::int8_t, 4> arr) {
    int ret = 0;
    for (int i = 0; i < 4; ++i) {
        ret = 19 * ret + (arr[i] + 9);
    }
    return ret;
}

int main() {
    long long silver = 0;
    std::vector<std::unordered_map<int, int>> monkeys;
    std::vector<std::int8_t> nums;
    nums.reserve(2001);
    for (int num; std::cin >> num; ) {
        nums.clear();
        nums.emplace_back(num % 10);
        for (int i = 0; i < 2000; ++i) {
            num = nextSecret(num);
            nums.emplace_back(num % 10);
        }
        silver += num;
        std::unordered_map<int, int> db;
        for (int i = 1; i + 4 <= nums.size(); ++i) {
            std::array<std::int8_t, 4> pattern;
            for (int j = 0; j < 4; ++j) {
                pattern[j] = nums[i+j] - nums[i+j-1];
            }
            db.emplace(hashArray(pattern), nums[i+3]);
        }
        monkeys.emplace_back(std::move(db));
    }
    std::cout << "silver: " << silver << '\n';
    int gold = 0;
    std::unordered_set<int> met;
    for (int i = 0; i < monkeys.size(); ++i) {
        for (auto [h, tmp] : monkeys[i]) {
            if (met.contains(h)) {
                continue;
            }
            met.emplace(h);
            int sum = 0;
            for (int j = i; j < monkeys.size(); ++j) {
                auto it = monkeys[j].find(h);
                if (it != monkeys[j].end()) {
                    sum += it->second;
                }
            }
            if (sum > gold) {
                gold = sum;
            }
        }
    }
    std::cout << "gold: " << gold << '\n';
}