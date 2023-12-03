#include <charconv>
#include <cctype>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

std::vector<std::string> scheme;
int m, n;

struct Number {
    int i, l, r;
};

std::optional<Number> get_number(int i, int j)
{
    if (0 <= i && i < m && 0 <= j && j < n && std::isdigit(scheme[i][j])) {
        int l = j, r = j;
        while (1 <= l && std::isdigit(scheme[i][l-1])) --l;
        while (r < n && std::isdigit(scheme[i][r])) ++r;
        std::optional<Number> ret;
        ret.emplace(i, l, r);
        return ret;
    }
    else {
        return {};
    }
}

std::vector<Number> find_numbers(int i, int j)
{
    std::vector<Number> ret;
    for (int ii = i - 1; ii <= i + 1; ++ii)
        for (int jj = j - 1; jj <= j + 1; ) {
            if (auto number = get_number(ii, jj)) {
                ret.emplace_back(*number);
                jj = number->r + 1;
            }
            else {
                ++jj;
            }
        }
    return ret;
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
        for (int j = 0; j < n; ++j)
            if (scheme[i][j] == '*') {
                auto numbers = find_numbers(i, j);
                if (numbers.size() == 2) {
                    long long add = 1;
                    for (const auto [ ii, l, r ] : numbers) {
                        long long mul = 1;
                        std::from_chars(scheme[ii].c_str() + l, scheme[ii].c_str() + r, mul);
                        add *= mul;
                    }
                    ret += add;
                }
            }
    std::cout << ret << '\n';
}