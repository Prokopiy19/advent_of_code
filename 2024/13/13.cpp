#include <algorithm>
#include <charconv>
#include <iostream>
#include <string>

int main() {
    int silver = 0;
    for (std::string line; std::getline(std::cin, line); ) {
        auto pos = line.find('X');
        int x1 = (line[pos+2] - '0') * 10 + line[pos+3] - '0';
        pos = line.find('Y');
        int y1 = (line[pos+2] - '0') * 10 + line[pos+3] - '0';

        std::getline(std::cin, line);
        pos = line.find('X');
        int x2 = (line[pos+2] - '0') * 10 + line[pos+3] - '0';
        pos = line.find('Y');
        int y2 = (line[pos+2] - '0') * 10 + line[pos+3] - '0';

        int x, y;
        std::getline(std::cin, line);
        pos = line.find('X');
        std::from_chars(line.c_str() + pos + 2, line.c_str() + line.size(), x);
        pos = line.find('Y');
        std::from_chars(line.c_str() + pos + 2, line.c_str() + line.size(), y);
        std::getline(std::cin, line);
        
        std::cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << ' ' << x << ' ' << y << '\n';
        
        int min_cost = INT_MAX;
        int i = 0;
        for (int xx = 0; xx <= x; xx += x1, ++i) {
            if ((x - xx) % x2 != 0) {
                continue;
            }
            int k = (x - xx) / x2;
            if (i * y1 + k * y2 != y) {
                continue;
            } 
            min_cost = std::min(min_cost, 3 * i + k);
        }
        if (min_cost < INT_MAX) {
            silver += min_cost;
        }
    }
    std::cout << silver << '\n';
}