#include <iostream>
#include <string>
#include <unordered_map>

int m;
int n;
char grid[3000][6000];

struct Robot {
    int i;
    int j;
};

struct Dir {
    int di;
    int dj;
};

bool isBox(int i, int j) {
    return grid[i][j] == '[' || grid[i][j] == ']';
}

bool testMove(int i, int j, Dir dir) {
    if (grid[i][j] == ']') {
        --j;
    }
    int ni = i + dir.di;
    int nj = j + dir.dj;
    if (grid[ni][nj] == '#' || grid[ni][nj+1] == '#') {
        return false;
    }
    grid[i][j] = grid[i][j+1] = '.';
    bool result = true;
    if (isBox(ni, nj) && !testMove(ni, nj, dir)) {
        result = false;
    }
    if (isBox(ni, nj + 1) && !testMove(ni, nj + 1, dir)) {
        result = false;
    }
    grid[i][j]   = '[';
    grid[i][j+1] = ']';
    return result;
}

void moveBox(int i, int j, Dir dir) {
    if (grid[i][j] == ']') {
        --j;
    }
    int ni = i + dir.di;
    int nj = j + dir.dj;
    grid[i][j] = grid[i][j+1] = '.';
    if (isBox(ni, nj)) {
        moveBox(ni, nj, dir);
    }
    if (isBox(ni, nj + 1)) {
        moveBox(ni, nj + 1, dir);
    }
    grid[ni][nj]   = '[';
    grid[ni][nj+1] = ']';
}

void printGrid(int i, int j) {
    // grid[i][j] = '@';
    // for (int i = 0; i < m; ++i) {
    //     for (int j = 0; j < n; ++j) {
    //         std::cout << grid[i][j];
    //     }
    //     std::cout << '\n';
    // }
    // std::cout << '\n';
    // grid[i][j] = '.';
}

signed main() {
    std::string line;
    for (int i = 0; std::getline(std::cin, line); ++i) {
        if (line.empty()) {
            break;
        }
        int j = 0;
        for (char c : line) {
            if (c == '@') {
                grid[i][j++] = '@';
                grid[i][j++] = '.';
            } else if (c != 'O') {
                grid[i][j++] = c;
                grid[i][j++] = c;
            } else {
                grid[i][j++] = '[';
                grid[i][j++] = ']';
            }
        }
        n = j;
    }
    m = n / 2;
    std::cout << m << ' ' << n << std::endl;

    std::string moves;
    while (std::cin >> line) {
        moves += line;
    }
    Robot robot;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == '@') {
                robot.i = i;
                robot.j = j;
                grid[i][j] = '.';
                break;
            }
        }
    }
    printGrid(robot.i, robot.j);

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
            case ']':
            case '[': {
                if (testMove(ni, nj, {di, dj})) {
                    moveBox(ni, nj, {di, dj});
                    robot = {ni, nj};
                }
                break;
            }
        }
        printGrid(robot.i, robot.j);
    }
    long long gold = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == '[') {
                gold += 100 * i + j;
            }
        }
    }
    std::cout << gold << '\n';
}