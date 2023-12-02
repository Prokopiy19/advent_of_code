#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

int main()
{
    int ans = 0;
    std::ifstream file("input.txt");
    for (std::string line; std::getline(file, line); ) {
        std::istringstream record(line);

        std::string skip;
        int id;
        record >> skip >> id >> skip;

        std::unordered_map<char, int> maxs;
        std::string color;
        for (int cnt; record >> cnt; ) {
            record >> color;
            maxs[color[0]] = std::max(maxs[color[0]], cnt);
        }
        int power = 1;
        for (auto& [color, cnt] : maxs) {
            power *= cnt;
        }
        ans += power;
    }
    std::cout << ans << '\n';
}