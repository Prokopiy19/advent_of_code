#include <cstdint>
#include <iostream>
#include <limits>
#include <string>

constexpr int N = 44;

int n;
char grid[N][N];
std::int8_t dp[N][N];

constexpr auto INF = std::numeric_limits<std::int8_t>::max();

int dfs(int i, int j, char c) {
    if (grid[i][j] != c) {
        return 0;
    }
    if (dp[i][j] < INF) {
        return dp[i][j];
    }
    if (c == '9') {
        return dp[i][j] = 1;
    }
    int ret = 0;
    ret += dfs(i - 1, j, c + 1);
    ret += dfs(i, j - 1, c + 1);
    ret += dfs(i, j + 1, c + 1);
    ret += dfs(i + 1, j, c + 1);
    return ret;
}

int main() {
    std::fill_n(&grid[0][0], N * N, '.');
    std::fill_n(&dp[0][0], N * N, INF);
    std::string line;
    for (int i = 1; std::getline(std::cin, line); ++i) {
        std::copy(line.cbegin(), line.cend(), &grid[i][1]);
        n = std::ssize(line);
    }
    int silver = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (grid[i][j] == '0') {
                silver += dfs(i, j, '0');
                std::cout << i << ' ' << j << ' ' << dfs(i, j, '0') << '\n';
            }
        }
    }
    std::cout << silver << '\n';
}