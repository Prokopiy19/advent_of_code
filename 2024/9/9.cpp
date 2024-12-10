#include <iostream>
#include <list>
#include <string>
#include <iterator>
#include <utility>
#include <vector>

constexpr int kEmpty = -1;

void print(const std::vector<int> &vec) {
    // for (int i : vec) {
    //     if (i != kEmpty) {
    //         std::cout << i;
    //     } else {
    //         std::cout << '.';
    //     }
    // }
    // std::cout << std::endl;
}

int main() {
    long long gold = 0;
    for (std::string line; std::getline(std::cin, line); ) {
        std::vector<int> filesystem;
        std::vector<std::pair<int, int>> blocks;
        std::vector<std::pair<int, int>> empty_spaces;
        for (int i = 0; i < std::ssize(line); ++i) {
            if (i % 2 == 0) {
                blocks.emplace_back(std::ssize(filesystem), line[i] - '0');
                for (int t = 0; t < line[i] - '0'; ++t) {
                    filesystem.emplace_back(i  / 2);
                }
            } else {
                empty_spaces.emplace_back(std::ssize(filesystem), line[i] - '0');
                for (int t = 0; t < line[i] - '0'; ++t) {
                    filesystem.emplace_back(kEmpty);
                }
            }
        }
        print(filesystem);
        for (int i = std::ssize(blocks) - 1; i > 0; --i) {
            for (auto &[j, sz] : empty_spaces) {
                if (j < blocks[i].first && sz >= blocks[i].second) {
                    for (int x = 0; x < blocks[i].second; ++x) {
                        filesystem[j + x] = i;
                        filesystem[blocks[i].first + x] = kEmpty;
                    }
                    blocks[i].first = j;
                    j += blocks[i].second;
                    sz -= blocks[i].second;
                }
            }
        }
        for (int i = 0; i < std::ssize(filesystem); ++i) {
            if (filesystem[i] != kEmpty) {
                gold += filesystem[i] * i;
            }
        }
        print(filesystem);
    }
    std::cout << gold << '\n';
}
