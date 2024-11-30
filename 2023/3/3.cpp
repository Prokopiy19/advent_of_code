#include <charconv>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> scheme;
int m, n;

inline
bool is_symbol(int i, int j)
{
    return 0 <= i && i < m && 0 <= j && j < n && !std::isdigit(scheme[i][j]) && scheme[i][j] != '.';
}

inline
bool is_adjacent(int i, int j)
{
    return is_symbol(i-1, j-1) || is_symbol(i-1, j) || is_symbol(i-1, j+1) ||
           is_symbol(i, j-1) || is_symbol(i, j+1) ||
           is_symbol(i+1, j-1) || is_symbol(i+1, j) || is_symbol(i+1, j+1);
}

bool is_part(int i, int l, int r)
{
    for (int j = l; j < r; ++j) {
        if (is_adjacent(i, j)) return true;
    }
    return false;
}

int main()
{
    for (std::string line; std::cin >> line; ) {
        scheme.emplace_back(std::move(line));
    }
    m = scheme.size();
    n = scheme[0].size();

    long long ret = 0;
    for (int i = 0; i < m; ++i)
        for (int l = 0; l < n; ) {
            int r = l;
            while (r < n && std::isdigit(scheme[i][r])) {
                ++r;
            }
            if (is_part(i, l, r)) {
                long long add = 0;
                std::from_chars(scheme[i].c_str() + l, scheme[i].c_str() + r, add);
                ret += add;
            }
            l = r + 1;
        }
    std::cout << ret << '\n';
}