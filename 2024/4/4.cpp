#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

const std::string pattern = "XMAS";
std::vector<std::string> board(3);

bool check(int i, int j, int step_i, int step_j) {
    for (int x = 0; x < 4; ++x) {
        if (board[i][j] != pattern[x]) {
            return false;
        }
        i += step_i;
        j += step_j;
    }
    return true;
}

int main() {
    int m = 0;
    int n = 0;
    std::string line;
    while (std::getline(std::cin, line)) {
        ++m;
        n = std::ssize(line);
        line = "..." + line + "...";
        board.emplace_back(line);
    }
    std::fill(line.begin(), line.end(), '.');
    // padding
    board[0] = line;
    board[1] = line;
    board[2] = line;
    board.emplace_back(line);
    board.emplace_back(line);
    board.emplace_back(line);
    
    int silver = 0;
    for (int i = 3; i < 3 + m; ++i) {
        for (int j = 3; j < 3 + n; ++j) {
            silver += check(i, j, 0, 1);
            silver += check(i, j, 0, -1);
            silver += check(i, j, -1, -1);
            silver += check(i, j, -1, 0);
            silver += check(i, j, -1, 1);
            silver += check(i, j, 1, -1);
            silver += check(i, j, 1, 0);
            silver += check(i, j, 1, 1);
        }
    }
    std::cout << silver << std::endl;

    int gold = 0;
    for (int i = 3; i < 3 + m; ++i) {
        for (int j = 3; j < 3 + n; ++j) {
            if (board[i][j] == 'A') {
                if (board[i-1][j-1] == 'M' && board[i+1][j+1] == 'S' || board[i-1][j-1] == 'S' && board[i+1][j+1] == 'M') {
                    if (board[i-1][j+1] == 'M' && board[i+1][j-1] == 'S' || board[i-1][j+1] == 'S' && board[i+1][j-1] == 'M') {
                        ++gold;
                    }
                }
            }
        }
    }
    std::cout << gold << std::endl;
}