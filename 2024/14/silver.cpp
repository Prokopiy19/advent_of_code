#include <cctype>
#include <iostream>
#include <sstream>
#include <string>

signed main() {
    constexpr int w = 101;
    constexpr int h = 103;
    std::string line;
    int cnt[2][2]{};
    for (int i = 0; std::getline(std::cin, line); ) {
        for (auto &c : line) if (!std::isdigit(c) && c != '-') c = ' ';
        std::istringstream record{line};
        int px, py, vx, vy;
        record >> px >> py >> vx >> vy;
        px = (px + 100 * vx) % w;
        py = (py + 100 * vy) % h;
        while (px < 0) px += w;
        while (py < 0) py += h;
        if (px == w / 2 || py == h / 2) {
            continue;
        }
        ++cnt[2 * px / w][2 * py / h];
        std::cout << px << ' ' << py << ' ' << 2 * px / w << ' ' << 2 * py / h << '\n';
    }
    long long silver = 1;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            std::cout << cnt[i][j] << ' ';
            silver *= cnt[i][j];
        }
        std::cout << '\n';
    }
    std::cout << silver << '\n';
}