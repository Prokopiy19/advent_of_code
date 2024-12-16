#include <algorithm>
#include <array>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

constexpr int N = 141;

std::array<std::pair<int, int>, 4> dirs{{
    {0, 1},
    {-1, 0},
    {0, -1},
    {1, 0},
}};

enum Dir { kRight, kUp, kLeft, kDown };

struct Entry {
    int dist;
    int i;
    int j;
    Dir dir;
    bool operator<(Entry rhs) const noexcept {
        return dist < rhs.dist;
    }
};

struct Bloat {
    int dist = INT_MAX;
    std::vector<Entry> prev;
    bool operator<(Bloat rhs) const noexcept {
        return dist < rhs.dist;
    }
};

int n;
char grid[N][N];
Bloat dp[N][N][4];
std::priority_queue<Entry> pq;

void findStart() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 'S') {
                pq.emplace(0, i, j, kRight);
                dp[i][j][kRight].dist = 0;
                return;
            }
        }
    }
}

std::pair<int, int> findExit() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 'E') {
                return {i, j};
            }
        }
    }
    return {};
}

int gold = 0;

void dfs(int i, int j, Dir dir) {
    if (dp[i][j][dir].dist == INT_MIN) {
        return;
    }
    dp[i][j][dir].dist = INT_MIN;
    if (grid[i][j] != 'O') {
        grid[i][j] = 'O';
        ++gold;
    }
    for (auto [dist, i, j, dir] : dp[i][j][dir].prev) {
        dfs(i, j, dir);
    }
}

int main() {
    std::string line;
    for (int i = 0; std::getline(std::cin, line); ++i) {
        std::copy(line.cbegin(), line.cend(), &grid[i][0]);
        n = line.size();
    }
    findStart();
    while (!pq.empty()) {
        auto prev = pq.top();
        auto [dist, i, j, dir] = prev;
        pq.pop();
        int ni = i + dirs[dir].first;
        int nj = j + dirs[dir].second;
        if (grid[ni][nj] != '#' && dist + 1 < dp[ni][nj][dir].dist) {
            dp[ni][nj][dir].dist = dist + 1;
            dp[ni][nj][dir].prev.clear();
            dp[ni][nj][dir].prev.emplace_back(prev);
            pq.emplace(dist + 1, ni, nj, dir);
        } else if (grid[ni][nj] != '#' && dist + 1 == dp[ni][nj][dir].dist) {
            dp[ni][nj][dir].prev.emplace_back(prev);
        }
        Dir ndir = static_cast<Dir>((dir + 1) % 4);
        if (dist + 1000 < dp[i][j][ndir].dist) {
            dp[i][j][ndir].dist = dist + 1000;
            dp[i][j][ndir].prev.clear();
            dp[i][j][ndir].prev.emplace_back(prev);
            pq.emplace(dist + 1000, i, j, ndir);
        } else if (dist + 1000 == dp[i][j][ndir].dist) {
            dp[i][j][ndir].prev.emplace_back(prev);
        }
        ndir = static_cast<Dir>((dir - 1 >= 0) ? dir - 1 : 3);
        if (dist + 1000 < dp[i][j][ndir].dist) {
            dp[i][j][ndir].dist = dist + 1000;
            dp[i][j][ndir].prev.clear();
            dp[i][j][ndir].prev.emplace_back(prev);
            pq.emplace(dist + 1000, i, j, ndir);
        } else if (dist + 1000 == dp[i][j][ndir].dist) {
            dp[i][j][ndir].prev.emplace_back(prev);
        }
    }
    auto [ei, ej] = findExit();
    auto it = std::min_element(&dp[ei][ej][0], &dp[ei][ej][4]);
    std::cout << it->dist << '\n';
    for (int i = 0; i < 4; ++i) {
        if (dp[ei][ej][i].dist == it->dist) {
            dfs(ei, ej, static_cast<Dir>(i));
        }
    }
    std::cout << gold << '\n';
}