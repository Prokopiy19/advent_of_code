#include <charconv>
#include <iostream>
#include <iterator>
#include <string>
#include <string_view>
#include <vector>

long long f10(long long n) {
    long long ret = 10;
    while (ret <= n) {
        ret *= 10;
    }
    return ret;
}

std::vector<long long> nums;

void parse(std::string_view s) {
    nums.clear();
    int num;
    auto p = s.data();
    const auto last = s.data() + s.size();
    std::from_chars_result result;
    for (auto p = s.data(); p != last; p = result.ptr) {
        result = std::from_chars(p + 1, last, num);
        nums.emplace_back(num);
    }
}

bool solve1(long long rhs, int i) {
    if (i == 0) {
        return nums[0] == rhs;
    }
    if (rhs - nums[i] >= 0 && solve1(rhs - nums[i], i - 1)) {
        return true;
    }
    if (rhs % nums[i] == 0 && solve1(rhs / nums[i], i - 1)) {
        return true;
    }
    return false;
}


bool solve2(long long rhs, int i) {
    if (i == 0) {
        return nums[0] == rhs;
    }
    if (rhs - nums[i] > 0 && solve2(rhs - nums[i], i - 1)) {
        return true;
    }
    if (rhs % nums[i] == 0 && solve2(rhs / nums[i], i - 1)) {
        return true;
    }
    long long n10 = f10(nums[i]);
    if (rhs % n10 == nums[i] && solve2(rhs / n10, i - 1)) {
        return true;
    }
    return false;
}

int main() {
    long long silver = 0;
    long long gold = 0;
    for (std::string line; std::getline(std::cin, line); ) {
        long long lhs;
        auto result = std::from_chars(line.c_str(), line.c_str() + line.size(), lhs);
        parse(std::string_view{result.ptr + 1, line.c_str() + line.size()});
        if (solve1(lhs, ssize(nums) - 1)) {
            silver += lhs;
            gold += lhs;
        } else if (solve2(lhs, ssize(nums) - 1)) {
            gold += lhs;
        }
    }
    std::cout << "silver: " << silver << '\n';
    std::cout << "gold:   " << gold << '\n';
}