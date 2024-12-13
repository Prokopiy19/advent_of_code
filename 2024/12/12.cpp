#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

constexpr int N = 142;
char grid[N][N];
int region[N][N]{};

struct RegionInfo {
    int s = 0;
    int p = 0;
    int n = 0;
    char c;
};

std::vector<RegionInfo> info(1);

void dfs(int i, int j, int id, char c) {
    if (grid[i][j] != c || region[i][j] != 0) {
        return;
    }
    region[i][j] = id;
    info[id].s++;
    dfs(i-1, j, id, c);
    dfs(i+1, j, id, c);
    dfs(i, j-1, id, c);
    dfs(i, j+1, id, c);
}

int main() {
    std::fill_n(&grid[0][0], N * N, '.');
    std::string line;
    int n;
    for (int i = 1; std::getline(std::cin, line); ++i) {
        std::copy(line.cbegin(), line.cend(), &grid[i][1]);
        std::cout << line << '\n';
        n = line.size();
    }
    int id = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (region[i][j] == 0) {
                info.emplace_back();
                info.back().c = grid[i][j];
                dfs(i, j, id++, grid[i][j]);
            }
        }
    }
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (region[i][j] != region[i+1][j]) {
                info[region[i][j]].p++;
                info[region[i+1][j]].p++;
            }
            if (region[i][j] != region[i][j+1]) {
                info[region[i][j]].p++;
                info[region[i][j+1]].p++;
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        int prev = 0;
        for (int j = 1; j <= n; ++j) {
            if (region[i-1][j] != region[i][j]) {
                if (region[i][j] != prev) {
                    info[region[i][j]].n++;
                    prev = region[i][j];
                }
            } else {
                prev = 0;
            }
        }
        prev = 0;
        for (int j = 1; j <= n; ++j) {
            if (region[i+1][j] != region[i][j]) {
                if (region[i][j] != prev) {
                    info[region[i][j]].n++;
                    prev = region[i][j];
                }
            } else {
                prev = 0;
            }
        }
    }
    for (int j = 1; j <= n; ++j) {
        int prev = 0;
        for (int i = 1; i <= n; ++i) {
            if (region[i][j-1] != region[i][j]) {
                if (region[i][j] != prev) {
                    info[region[i][j]].n++;
                    prev = region[i][j];
                }
            } else {
                prev = 0;
            }
        }
        prev = 0;
        for (int i = 1; i <= n; ++i) {
            if (region[i][j+1] != region[i][j]) {
                if (region[i][j] != prev) {
                    info[region[i][j]].n++;
                    prev = region[i][j];
                }
            } else {
                prev = 0;
            }
        }
    }
    long long silver = 0;
    for (int i = 1; i < info.size(); ++i) {
        silver += info[i].p * info[i].s;
    }
    long long gold = 0;
    for (int i = 1; i < info.size(); ++i) {
        gold += info[i].n * info[i].s;
    }
    std::cout << "silver: " << silver << '\n';
    std::cout << "gold:   " << gold << '\n';
}