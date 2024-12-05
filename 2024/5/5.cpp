#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

bool rules[100][100]{};

int main() {
    int silver = 0;
    int gold = 0;
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line[2] != '|') {
            break;
        }
        line[2] = ' ';
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
        for (int i = 0; i < std::ssize(nums); ++i) {
            for (int j = i + 1; j < std::ssize(nums); ++j) {
                if (rules[nums[j]][nums[i]]) {
                    correct = false;
                    break;
                }
            }
            if (!correct) {
                break;
            }
        }
        if (correct) {
            silver += nums[std::ssize(nums) / 2];
            continue;
        }
        std::sort(nums.begin(), nums.end(), [](int lhs, int rhs) {
            return rules[lhs][rhs];
        });
        gold += nums[std::ssize(nums) / 2];
    }
    std::cout << silver << std::endl;
    std::cout << gold << std::endl;
}