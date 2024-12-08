#include <iostream>
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

void f(int x, int y) {
    if (0 <= x && x < n && 0 <= y && y < n && board[x][y] != '#') {
        board[x][y] = '#';
        ++cnt;
    }
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
                f(vec[i].x - dx, vec[i].y - dy);
                f(vec[j].x + dx, vec[j].y + dy);
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