#include <cstdint>
#include <iostream>
#include <limits>
#include <string>

constexpr int N = 44;

int n;
char grid[N][N];
std::int16_t vis[N][N]{};

int silver = 0;
int id = 1;

constexpr auto INF = std::numeric_limits<std::int8_t>::max();

void dfs(int i, int j, char c) {
    if (grid[i][j] != c) {
        return;
    }
    if (vis[i][j] == id) {
        return;
    }
    if (c == '9') {
        if (vis[i][j] != id) {
            ++silver;
            vis[i][j] = id;
        }
        return;
    }
    vis[i][j] = id;
    dfs(i - 1, j, c + 1);
    dfs(i, j - 1, c + 1);
    dfs(i, j + 1, c + 1);
    dfs(i + 1, j, c + 1);
    return;
}

int main() {
    std::fill_n(&grid[0][0], N * N, '.');
    std::string line;
    for (int i = 1; std::getline(std::cin, line); ++i) {
        std::copy(line.cbegin(), line.cend(), &grid[i][1]);
        n = std::ssize(line);
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (grid[i][j] == '0') {
                dfs(i, j, '0');
                ++id;
                // std::cout << i << ' ' << j << ' ' << silver << '\n';
            }
        }
    }
    std::cout << silver << '\n';
}