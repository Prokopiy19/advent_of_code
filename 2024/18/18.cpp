#include <algorithm>
#include <iostream>
#include <iterator>
#include <ostream>
#include <queue>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

struct Coordinate {
    int r;
    int c;
};

constexpr int N = 73;
int n = 71;

char grid[N][N];
int dp[N][N];
std::queue<Coordinate> q;
std::queue<Coordinate> q_nxt;
std::vector<Coordinate> bytes;

void print() {
    for (int i = 0; i <= n + 1; ++i) {
        for (int j = 0; j <= n + 1; ++j) {
            std::cout << grid[i][j];
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

void go(int r, int c, int dist) {
    if (grid[r][c] == '#') {
        return;
    }
    if (dist < dp[r][c]) {
        dp[r][c] = dist;
        q_nxt.emplace(r, c);
    }
}

bool solve(int num_bytes) {
    for (int i = 1; i <= n; ++i) {
        std::fill_n(&grid[i][1], n, '.');
    }
    std::fill_n(&dp[0][0], N * N, INT_MAX);
    for (int i = 0; i < num_bytes; ++i) {
        grid[bytes[i].r][bytes[i].c] = '#';
    }

    q.emplace(1, 1);
    dp[1][1] = 0;
    int dist = 1;
    while (!q.empty()) {
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            go(r - 1, c, dist);
            go(r + 1, c, dist);
            go(r, c - 1, dist);
            go(r, c + 1, dist);
        }
        ++dist;
        std::swap(q, q_nxt);
    }
    return dp[n][n] < INT_MAX;
}



int main() {
    std::fill_n(&grid[0][0], N * N, '#');
    std::string line;
    for (int i = 0; std::getline(std::cin, line); ++i) {
        for (char &c : line) if (c == ',') c = ' ';
        std::istringstream record{line};
        int x, y;
        record >> x >> y;
        bytes.emplace_back(y+1, x+1);
    }
    for (int i = 1; i <= n; ++i) {
        grid[i][n+1] = '#';
    }
    std::fill_n(&grid[n+1][1], n+1, '#');

    int l = 1;
    int r = std::ssize(bytes);

    while (l < r) {
        int m = (l + r) / 2;
        if (solve(m)) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    std::cout << l << ' ' << bytes[l-1].c - 1 << ',' << bytes[l-1].r - 1 << '\n';
}