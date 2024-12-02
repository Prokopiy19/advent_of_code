#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

bool checkSafety(const std::vector<int> &nums) {
    for (int i = 0; i + 1 < ssize(nums); ++i) {
        auto diff = nums[i + 1] - nums[i];
        if (diff < 1 || 3 < diff) {
            return false;
        }
    }
    return true;
}

int main() {
    int gold = 0;
    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream record{line};
        std::vector<int> nums;
        int num;
        while (record >> num) {
            nums.emplace_back(num);
        }
        if (checkSafety(nums)) {
            ++gold;
            continue;
        }
        std::reverse(nums.begin(), nums.end());
        if (checkSafety(nums)) {
            ++gold;
            continue;
        }
        std::reverse(nums.begin(), nums.end());
        int tmp = nums.back();
        nums.pop_back();
        int swp = std::ssize(nums);
        while (swp >= 0) {
            if (checkSafety(nums)) {
                ++gold;
                break;
            }
            std::reverse(nums.begin(), nums.end());
            if (checkSafety(nums)) {
                ++gold;
                break;
            }
            std::reverse(nums.begin(), nums.end());
            --swp;
            if (swp >= 0) {
                std::swap(nums[swp], tmp);
            }
        }
    }
    std::cout << gold;
}