#include <iostream>
#include <fstream>
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
        bool correct = true;
        std::string color;
        for (int cnt; record >> cnt; ) {
            record >> color;
            color.pop_back();
            if (color == "red" && cnt > 12 || color == "green" && cnt > 13 || color == "blue" && cnt > 14) {
                correct = false;
                break;
            }
        }
        if (correct) ans += id;
    }
    std::cout << ans << '\n';
}