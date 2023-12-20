#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Segment {
    int x0, x1, y;
};

signed main()
{
    std::vector<Segment> segments;
    int x = 0;
    int y = 1;
    for (char dir; std::cin >> dir; ) {
        int steps;
        std::string hex;
        std::cin >> steps >> hex;
        
        hex = hex.substr(2);
        hex.pop_back();
        
        dir = hex.back();
        
        hex.pop_back();
        
        steps = std::stoi(hex, nullptr, 16);
        
        int to_x = x;
        switch(dir) {
            case 'R': case '0': to_x += steps; break;
            case 'D': case '1': y += steps; break;
            case 'L': case '2': to_x -= steps; break;
            case 'U': case '3': y -= steps; break;
        }
        if (x != to_x) {
            segments.emplace_back(x, to_x, y);
        }
    }
    const int n = segments.size();
    long long part_two = 0;
    for (int i = 0; i < n; ++i) {
        auto& segment = segments[i];
        int j = i - 1;
        j = (j < 0) ? j + n : j;
        const auto& prv = segments[j];
        j = i + 1;
        j = (j == n) ? j = 0 : j;
        const auto& nxt = segments[j];
        if (segment.x0 < segment.x1) {
            if (prv.y < segment.y) {
                ++segment.x0;
            }
            if (nxt.y < segment.y) {
                --segment.x1;
            }
            part_two -= (segment.x1 - segment.x0 + 1) * (segment.y - 1LL);
        }
        else {
            if (prv.y > segment.y) {
                --segment.x0;
            }
            if (nxt.y > segment.y) {
                ++segment.x1;
            }
            part_two += (segment.x0 - segment.x1 + 1) * 1LL * segment.y;
        }
    }
    std::cout << part_two << '\n';
}