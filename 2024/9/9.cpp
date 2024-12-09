#include <iostream>
#include <list>
#include <string>
#include <iterator>
#include <utility>
#include <vector>

constexpr int kEmpty = -1;

int main() {
    long long silver = 0;
    for (std::string line; std::getline(std::cin, line); ) {
        std::vector<int> filesystem;
        // std::list<std::pair<int, int>> empty_spaces;
        for (int i = 0; i < std::ssize(line); ++i) {
            if (i % 2 == 0) {
                for (int t = 0; t < line[i] - '0'; ++t) {
                    filesystem.emplace_back(i  / 2);
                }
            } else {
                for (int t = 0; t < line[i] - '0'; ++t) {
                    filesystem.emplace_back(kEmpty);
                }
            }
        }
        for (int i = 0; i < std::ssize(filesystem); ++i) {
            if (filesystem[i] == kEmpty) {
                filesystem[i] = filesystem.back();
                filesystem.pop_back();
            }
            while (filesystem.back() == kEmpty) {
                filesystem.pop_back();
            }
        }
        for (int i = 0; i < std::ssize(filesystem); ++i) {
            silver += filesystem[i] * i;
        }
    }
    std::cout << silver << '\n';
}
