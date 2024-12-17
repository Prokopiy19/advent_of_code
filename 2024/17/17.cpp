#include <algorithm>
#include <array>
#include <cassert>
#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define int long long

std::vector<int> nums;
std::array<int, 3> reg{};

void init(int a) {
    reg[0] = a;
    reg[1] = reg[2] = 0;
}

int combo(int op) {
    if (op <= 3) {
        return op;
    } else if (op <= 6) {
        return reg[op - 4];
    }
    assert(false);
    return {};
}

signed main() {
    std::string line;
    for (int i = 0; i < 3; ++i) {
        std::getline(std::cin, line);
        for (char &c : line) {
            if (!std::isdigit(c)) {
                c = ' ';
            }
        }
        std::istringstream record{line};
        record >> reg[i];
    }
    std::getline(std::cin, line);
    std::getline(std::cin, line);
    for (char &c : line) {
        if (!std::isdigit(c)) {
            c = ' ';
        }
    }
    std::istringstream record{line};
    for (int num; record >> num; ) {
        nums.emplace_back(num);
    }
    std::vector<int> output;
    int &a = reg[0];
    int &b = reg[1]; // 105692700000000
    int &c = reg[2];
    for (int x = 105734710000000; output.size() <= nums.size(); x++) {
        output.clear();
        init(x);
        for (int i = 0; i + 1 < nums.size(); ++i) {
            switch (nums[i++]) {
                case 0: {
                    a /= (1 << combo(nums[i]));
                    break;
                }
                case 1: {
                    b ^= nums[i];
                    break;
                }
                case 2: {
                    b = combo(nums[i]) & 0b111;
                    break;
                }
                case 3: {
                    if (a) {
                        i = nums[i] - 1; // -1 to compensate ++i
                    }
                    break;
                }
                case 4: {
                    b ^= c;
                    break;
                }
                case 5: {
                    output.emplace_back(combo(nums[i]) & 0b111);
                    break;
                }
                case 6: {
                    b = a / (1 << combo(nums[i]));
                    break;
                }
                case 7: {
                    c = a / (1 << combo(nums[i]));
                    break;
                }
            }
        }
        if (output == nums) {
            std::cout << "gold: " << x << '\n';
            return 0;
        }
        if (x % 10'000'000 == 0) {
        // if (true) {
            std::cout << x << ' ';
            if (!output.empty()) {
                std::cout << output[0];
            }
            for (int i = 1; i < output.size(); ++i) {
                std::cout << ',' << output[i];
            }
            std::cout << std::endl;
            // if (output[9] == 6 && output[10] == 0 ) {
            //     return 0;
            // }
        }
    }
}