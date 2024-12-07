#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

int binpow(int a, int n) {
    int res = 1;
    while (n) {
        if (n & 1)
            res *= a;
        a *= a;
        n >>= 1;
    }
    return res;
}

int count_digits(long long num) {
    return std::to_string(num).size();
}

int main() {
    long long gold = 0;
    std::vector<long long> nums;
    for (std::string line; std::getline(std::cin, line); ) {
        std::istringstream record{line};
        long long lhs;
        char c;
        record >> lhs >> c;
        nums.clear();
        for (int num; record >> num; ) {
            nums.emplace_back(num);
        }
        unsigned lim = binpow(3, nums.size() - 1);
        for (unsigned mask = 0; mask < lim; ++mask) {
            unsigned tmp = mask;
            long long rhs = nums[0];
            for (int i = 1; i < std::ssize(nums); ++i) {
                switch (mask % 3) {
                    case 0: rhs *= nums[i]; break;
                    case 1: rhs += nums[i]; break;
                    case 2: rhs *= binpow(10, count_digits(nums[i])); rhs += nums[i]; break;
                }
                if (rhs > lhs) {
                    break;
                }
                mask /= 3;
            }
            if (lhs == rhs) {
                gold += lhs;
                break;
            }
            mask = tmp;
        }
    }
    std::cout << gold << std::endl;
}