#include <iostream>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <string>

std::unordered_map<char, int> maxs = { { 'r', 12 }, { 'g', 13 }, { 'b', 14 } };

int main()
{
    int ans = 0;
    std::ifstream file("input.txt");
    for (std::string line; std::getline(file, line); ) {
        std::istringstream record(line);

        std::string skip;
        int id;
        record >> skip >> id >> skip;

        bool correct = true;
        std::string color;
        for (int cnt; record >> cnt; ) {
            record >> color;
            if (cnt > maxs[color[0]]) {
                correct = false;
                break;
            }
        }
        if (correct) ans += id;
    }
    std::cout << ans << '\n';
}