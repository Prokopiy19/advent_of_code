#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <ostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

struct Coordinate {
    int r;
    int c;
};

constexpr int N = 142;
int n = 142;

int istart;
int jstart;

char grid[N][N];
int dp[N][N];
std::queue<Coordinate> q;
std::queue<Coordinate> q_nxt;

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

bool bfs() {
    std::fill_n(&dp[0][0], N * N, INT_MAX);

    q.emplace(istart, jstart);
    dp[istart][jstart] = 0;
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
    std::string line;
    for (int i = 0; std::getline(std::cin, line); ++i) {
        std::copy(line.cbegin(), line.cend(), &grid[i][0]);
        n = line.size();
    }

    int r, c;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 'S') {
                r = i;
                c = j;
            }
            if (grid[i][j] == 'E') {
                istart = i;
                jstart = j;
            }
        }
    }

    bfs();

    std::vector<int> silver;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j + 2 < n; ++j) {
            if (grid[i][j] != '#' && grid[i][j+1] == '#' && grid[i][j+2] != '#'
                    && dp[i][j] < INT_MAX && dp[i][j+2] < INT_MAX) {
                silver.emplace_back(std::abs(dp[i][j] - dp[i][j+2]) - 2);
            }
        }
    }

    for (int j = 0; j < n; ++j) {
        for (int i = 0; i + 2 < n; ++i) {
            if (grid[i][j] != '#' && grid[i+1][j] == '#' && grid[i+2][j] != '#'
                    && dp[i][j] < INT_MAX && dp[i+2][j] < INT_MAX) {
                silver.emplace_back(std::abs(dp[i][j] - dp[i+2][j]) - 2);
            }
        }
    }


    std::sort(silver.rbegin(), silver.rend());

    // for (int i : silver) {
    //     std::cout << i << '\n';
    // }

    int cnt = 0;

    for (int i : silver) {
        if (i >= 100) {
            cnt++;
        }
    }
    std::cout << cnt << '\n';

    int gold = 0;

    std::unordered_map<int, int> cheats;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == '#' || dp[i][j] == INT_MAX) {
                continue;
            }
            for (int ii = std::max(0, i-20); ii <= std::min(n-1, i+20); ++ii) {
                for (int jj = std::max(0, j-20); jj <= std::min(n-1, j+20); ++jj) {
                    if (int dist = std::abs(i - ii) + std::abs(j - jj); dist <= 20 && grid[ii][jj] != '#') {
                        if (dp[ii][jj] == INT_MAX) {
                            continue;
                        } 
                        cheats[std::abs(dp[i][j] - dp[ii][jj]) - dist]++;
                        if (std::abs(dp[i][j] - dp[ii][jj]) - dist >= 100) {
                            ++gold;
                        }
                    }
                }
            }
        }
    }
    std::vector<std::pair<int, int>> output;
    for (auto [i, cnt] : cheats) {
        if (i >= 50) {
            output.emplace_back(i, cnt / 2);
        }
    }
    std::sort(output.begin(), output.end());
    for (auto [x, y] : output) {
        std::cout << x << ' ' << y << '\n';
    }
    std::cout << "gold: " << gold / 2 << '\n';
}