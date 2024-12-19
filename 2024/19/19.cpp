#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>

#define int long long

std::unordered_set<std::string> towels;
std::unordered_map<std::string, int> memo;

int dfs(std::string_view s) {
    if (memo.contains(std::string(s))) {
        return memo[std::string(s)];
    }
    if (s.empty()) {
        return memo[std::string(s)] = 1;
    }
    int ret = 0;
    for (int i = 1; i <= s.size(); ++i) {
        if (towels.contains(std::string(s.substr(0, i)))) {
            ret += dfs(s.substr(i));
        }
    }
    return memo[std::string(s)] = ret;
}

signed main() {
    std::string line;
    std::getline(std::cin, line);
    for (char &c : line) if (c == ',') c = ' ';
    std::istringstream record{line};
    for (std::string word; record >> word; ) {
        towels.emplace(word);
    }
    std::getline(std::cin, line);
    int gold = 0;
    while (std::cin >> line) {
        gold += dfs(line);
    }
    std::cout << gold << '\n';
}