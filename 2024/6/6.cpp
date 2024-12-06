#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>

constexpr int N = 135;

int n;
char grid[N][N];

std::pair<int, int> find_start() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (grid[i][j] != '.' && grid[i][j] != '#') {
                return { i, j };
            }
        }
    }
    return {-1, -1};
}

int main() {
    std::fill_n(&grid[0][0], N * N, '$');
    int row = 1;
    for (std::string line; std::cin >> line; ) {
        n = std::ssize(line);
        std::copy(line.cbegin(), line.cend(), &grid[row][1]);
        ++row; 
    }
    auto [istart, jstart] = find_start();
    int gold = 0;
    for (int x = 1; x <= n; ++x) for (int y = 1; y <= n; ++y) if (grid[x][y] != '#') {
        grid[x][y] = '#';
        int i = istart;
        int j = jstart;
        int visited = 0;
        grid[i][j] = 'X';
        enum {
            kUp, kRight, kDown, kLeft
        } dir = kUp;
        bool exited = false;
        for (int x = 0; x < 10'000; ++x) {
            switch (dir) {
                case kUp: {
                    if (grid[i-1][j] == '#') {
                        dir = kRight;
                    } else {
                        --i;
                    }
                    break;
                }
                case kRight: {
                    if (grid[i][j+1] == '#') {
                        dir = kDown;
                    } else {
                        ++j;
                    }
                    break;
                }
                case kDown: {
                    if (grid[i+1][j] == '#') {
                        dir = kLeft;
                    } else {
                        ++i;
                    }
                    break;
                }
                case kLeft: {
                    if (grid[i][j-1] == '#') {
                        dir = kUp;
                    } else {
                        --j;
                    }
                    break;
                }
            }
            if (i == istart && j == jstart && dir == kUp) {
                break;
            }
            if (grid[i][j] == '$') {
                exited = true;
                break;
            }
            if (grid[i][j] == '.') {
                ++visited;
                grid[i][j] = 'X';
            }
        }
        if (!exited) {
            ++gold;
        }
        grid[x][y] = '.';
    }
    std::cout << gold;
}