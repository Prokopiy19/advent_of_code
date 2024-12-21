#include <algorithm>
#include <array>
#include <charconv>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>
#include <string_view>
#include <unordered_map>

constexpr int kSilverRobots = 4;
constexpr int kGoldRobots = 27;

struct Coord {
    int x, y;
};

std::array<Coord, std::numeric_limits<char>::max()> coords{};

void coordsInit() {
    coords['A'] = { 0, 0 };

    coords['^'] = { -1,  0 };
    coords['<'] = { -2, -1 };
    coords['v'] = { -1, -1 };
    coords['>'] = {  0, -1 };

    coords['0'] = { -1, 0 };
    coords['1'] = { -2, 1 };
    coords['2'] = { -1, 1 };
    coords['3'] = {  0, 1 };
    coords['4'] = { -2, 2 };
    coords['5'] = { -1, 2 };
    coords['6'] = {  0, 2 };
    coords['7'] = { -2, 3 };
    coords['8'] = { -1, 3 };
    coords['9'] = {  0, 3 };
}

struct Key {
    char from;
    char to;
    std::uint8_t n;
    bool operator==(Key rhs) const noexcept {
        return from == rhs.from && to == rhs.to && n == rhs.n;
    }
};

struct MyHash {
    std::size_t operator()(Key key) const noexcept {
        return (size_t(key.from) << 16) | size_t(key.to) << 8 | size_t(key.n);
    }
};

std::unordered_map<Key, long long, MyHash> memo;

long long dfs(char from, char to, std::uint8_t n);

long long solve(std::string_view s, std::uint8_t n) {
    long long ret = 0;
    for (int i = 0; i + 1 < s.size(); ++i) {
        ret += dfs(s[i], s[i+1], n-1);
    }
    return ret;
}

long long dfs(char from, char to, std::uint8_t n) {
    Key key{from, to, n};
    if (memo.contains(key)) {
        return memo[key];
    }
    if (n == 0) {
        return memo[key] = 1;
    }
    auto [x, y] = coords[from];
    auto [tx, ty] = coords[to];
    int dx = tx - x;
    int dy = ty - y;

    if (dx == 0) {
        char c = (dy < 0) ? 'v' : '^';
        std::string s = "A";
        s.append(std::abs(dy), c);
        s += 'A';
        return memo[key] = solve(s, n);
    } else if (dy == 0) {
        char c = (dx < 0) ? '<' : '>';
        std::string s = "A";
        s.append(std::abs(dx), c);
        s += 'A';
        return memo[key] = solve(s, n);
    } else if (dx != 0 && dy != 0) {
        char cx = (dx < 0) ? '<' : '>';
        char cy = (dy < 0) ? 'v' : '^';
        long long ret = std::numeric_limits<long long>::max();

        if (!(tx == -2 && y == 0)) {
            std::string variant1 = "A";
            variant1.append(std::abs(dx), cx);
            variant1.append(std::abs(dy), cy);
            variant1 += 'A';
            ret = std::min(ret, solve(variant1, n));
        }

        if (!(x == -2 && ty == 0)) {
            std::string variant2 = "A";
            variant2.append(std::abs(dy), cy);
            variant2.append(std::abs(dx), cx);
            variant2 += 'A';
            ret = std::min(ret, solve(variant2, n));
        }

        return memo[key] = ret;
    }
    return memo[key] = solve("AA", n);
}

int main() {
    coordsInit();
    std::string line;
    long long silver = 0;
    long long gold = 0;

    for (int i = 0; std::getline(std::cin, line); ++i) {
        int code;
        std::from_chars(line.c_str(), line.c_str() + line.size(), code);
        line.insert(line.begin(), 'A');
        std::cout << line << ' ' << solve(line, kSilverRobots) << '\n';
        silver += code * solve(line, kSilverRobots);
        gold   += code * solve(line, kGoldRobots);
    }
    std::cout << "silver: " << silver << '\n';
    std::cout << "gold  : " << gold << '\n';
}