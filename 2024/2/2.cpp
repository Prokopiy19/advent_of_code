#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

bool checkDiff(int x, int y) {
    auto diff = y - x;
    return 1 <= diff && diff <= 3;
}

int checkSafety(const std::vector<int> &nums, int skip = -1) {
    const int n = std::ssize(nums);
    for (int i = 0; i + 1 < skip; ++i)
        if (!checkDiff(nums[i], nums[i+1])) {
            return i;
        }
    if (0 <= skip - 1 && skip + 1 < n)
        if (!checkDiff(nums[skip-1], nums[skip+1])) {
            return skip;
        }
    for (int i = skip + 1; i + 1 < n; ++i)
        if (!checkDiff(nums[i], nums[i+1])) {
            return i;
        }
    return -1;
}


void solve(const std::vector<int> &nums, bool &s, bool &g) {
    int mistake = checkSafety(nums);
    if (mistake < 0) {
        s = true;
        g = true;
        return;
    }
    if (checkSafety(nums, mistake) < 0 || checkSafety(nums, mistake + 1) < 0) {
        g = true;
    }
}

int main() {

    int silver = 0;
    int gold = 0;
    std::string line;
    std::vector<int> nums;
    while (std::getline(std::cin, line)) {
        nums.clear();
        std::istringstream record{line};
        int num;
        while (record >> num) {
            nums.emplace_back(num);
        }
        bool s = false;
        bool g = false;
        solve(nums, s, g);
        if (!s) {
            std::reverse(nums.begin(), nums.end());
            solve(nums, s, g);
        }
        silver += s;
        gold += g;
    }
    std::cout << "silver: " << silver << '\n';
    std::cout << "gold: " << gold << std::endl;
}