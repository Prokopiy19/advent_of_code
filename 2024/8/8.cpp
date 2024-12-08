#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

struct Point {
    int x, y;
};


std::unordered_map<int, std::vector<Point>> antennas;

constexpr int N = 51;
int n;
char board[N][N];

int cnt = 0;

bool f(int x, int y) {
    if (0 <= x && x < n && 0 <= y && y < n) {
        if (board[x][y] != '#') {
            board[x][y] = '#';
            ++cnt;
        }
        return true;
    }
    return false;
}

int main() {
    int i = 0;
    for (std::string line; std::getline(std::cin, line); ) {
        std::istringstream record{line};
        std::copy(line.cbegin(), line.cend(), &board[i][0]);
        n = std::ssize(line);
        ++i;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (board[i][j] != '.') {
                antennas[board[i][j]].emplace_back(i, j);
            }
        }
    }
    for (auto &[c, vec] : antennas) {
        for (int i = 0; i < vec.size(); ++i) {
            for (int j = i+1; j < vec.size(); ++j) {
                int dx = vec[j].x - vec[i].x;
                int dy = vec[j].y - vec[i].y;
                int g = std::gcd(dx, dy);
                dx /= g;
                dy /= g;
                int x = vec[i].x;
                int y = vec[i].y;
                while (f(x, y)) {
                    x -= dx;
                    y -= dy;
                }
                x = vec[i].x;
                y = vec[i].y;
                while (f(x, y)) {
                    x += dx;
                    y += dy;
                }
            }
        }
    }
    std::cout << cnt << '\n';
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << board[i][j];
        }
        std::cout << std::endl;
    }
}