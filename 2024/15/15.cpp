#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>

constexpr int N = 51;

int n;
char grid[N][N];

struct Robot {
    int i;
    int j;
};

struct Dir {
    int di;
    int dj;
};

signed main() {
    std::string line;
    for (int i = 0; std::getline(std::cin, line); ++i) {
        if (line.empty()) {
            break;
        }
        std::copy(line.cbegin(), line.cend(), &grid[i][0]);
        n = line.size();
    }
    std::string moves;
    while (std::cin >> line) {
        moves += line;
    }
    Robot robot;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == '@') {
                robot.i = i;
                robot.j = j;
                grid[i][j] = '.';
                break;
            }
        }
    }
    std::unordered_map<char, Dir> dirs;
    dirs['^'] = { .di =-1, .dj = 0 };
    dirs['>'] = { .di = 0, .dj = 1 };
    dirs['v'] = { .di = 1, .dj = 0 };
    dirs['<'] = { .di = 0, .dj =-1 };
    for (char c : moves) {
        auto [di, dj] = dirs[c];
        int ni = robot.i + di;
        int nj = robot.j + dj;
        switch (grid[ni][nj]) {
            case '.': {
                robot = { .i = ni, .j = nj };
                break;
            }
            case '#': {
                break;
            }
            case 'O': {
                int ii = ni;
                int jj = nj;
                while (grid[ii][jj] == 'O') {
                    ii += di;
                    jj += dj;
                }
                if (grid[ii][jj] == '.') {
                    std::swap(grid[ii][jj], grid[ni][nj]);
                    robot = { ni, nj };
                }
                break;
            }
        }
    }
    long long silver = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 'O') {
                silver += 100 * i + j;
            }
        }
    }
    std::cout << silver << '\n';
}