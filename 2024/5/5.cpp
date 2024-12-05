#include <algorithm>
#include <bitset>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

std::bitset<10'000> rules[10'000];

int main() {
    int silver = 0;
    int gold = 0;
    std::string line;
    while (std::getline(std::cin, line)) {
        auto pos = line.find('|');
        if (pos == std::string::npos) {
            break;
        }
        line[pos] = ' ';
        std::istringstream record{line};
        int x, y;
        record >> x >> y;
        rules[x][y] = true;
    }
    std::vector<int> nums;
    while (std::getline(std::cin, line)) {
        nums.clear();
        for (char &c : line) if (c == ',') c = ' ';
        std::istringstream record{line};
        for (int num; record >> num; ) {
            nums.emplace_back(num);
        }
        bool correct = true;
        for (int i = 1; i < std::ssize(nums); ++i) {
            if (rules[nums[i]][nums[i-1]]) {
                correct = false;
                break;
            }
        }
        if (correct) {
            silver += nums[std::ssize(nums) / 2];
            continue;
        }
        std::nth_element(nums.begin(), nums.begin() + std::size(nums) / 2, nums.end(),
            [](int lhs, int rhs) {
                return rules[lhs][rhs];
            });
        gold += nums[std::ssize(nums) / 2];
    }
    std::cout << silver << std::endl;
    std::cout << gold << std::endl;
}