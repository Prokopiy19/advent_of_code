#include <charconv>
#include <iostream>
#include <string>

#define int long long

signed main() {
    int gold = 0;
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
        
        x += 10000000000000;
        y += 10000000000000;

        if ((x * y2 - x2 * y) % (x1 * y2 - y1 * x2) == 0) {
            int n = (x * y2 - x2 * y) / (x1 * y2 - y1 * x2);
            int dx = x - n * x1;
            int dy = y - n * y1;
            if (dx % x2 != 0 || dy % y2 != 0) {
                continue;
            }
            int m = dx / x2;
            if (y1 * n + y2 * m != y) {
                continue;
            }
            gold += 3 * n + m;
        }
    }
    std::cout << gold << '\n';
}