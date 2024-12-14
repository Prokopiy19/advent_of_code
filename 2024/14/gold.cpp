#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Robot {
    int px, py, vx, vy;
};

signed main() {
    constexpr int w = 101;
    constexpr int h = 103;
    std::vector<Robot> robots;
    for (std::string line; std::getline(std::cin, line); ) {
        for (auto &c : line) if (!std::isdigit(c) && c != '-') c = ' ';
        std::istringstream record{line};
        int px, py, vx, vy;
        record >> px >> py >> vx >> vy;
        robots.emplace_back(px, py, vx, vy);
    }
    char grid[w][h];
    int tmax = -1;
    int cntmax = -1;
    for (int t = 0; t < 1'000'00; ++t) {
        std::cout << t << '\n';
        std::fill_n(&grid[0][0], w * h, '.');
        for (auto robot : robots) {
            grid[robot.px][robot.py] = '*';
        }

        int cnt = 0;
        for (int y = 0; y < h; ++y) {
            for (int x = std::max(w / 2 - y, 0); x < std::min(w, w / 2 + y); ++x) {
                cnt += (grid[x][y] == '*');
            }
        }
        if (cnt > cntmax) {
            tmax = t;
            cntmax = cnt;
        }

        // for (int i = 0; i < w; ++i) {
        //     for (int j = 0; j < h; ++j) {
        //         std::cout << grid[i][j];
        //     }
        //     std::cout << '\n';
        // }
        // std::cout << '\n';
        for (auto &robot : robots) {
            robot.px += robot.vx;
            robot.px %= w;
            robot.py += robot.vy;
            robot.py %= h;
            while (robot.px < 0) robot.px += w;
            while (robot.py < 0) robot.py += h;
        }
    }
    std::cout << tmax << '\n';
}