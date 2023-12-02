#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <string>

int main()
{
    int ans = 0;
    std::ifstream file("input.txt");
    for (std::string line; std::getline(file, line); ) {
        line.push_back('.');
        std::istringstream record(line);
        std::string skip;
        int id;
        record >> skip >> id >> skip;
        std::map<std::string, int> maxs;
        std::string color;
        for (int cnt; record >> cnt; ) {
            record >> color;
            color.pop_back();
            maxs[color] = std::max(maxs[color], cnt);
        }
        int power = 1;
        for (auto& [color, cnt] : maxs) {
            power *= cnt;
        }
        ans += power;
    }
    std::cout << ans << '\n';
}