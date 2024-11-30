#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main()
{
    std::ifstream in("input.txt", std::ios_base::in);
    long long ret = 0;
    std::vector<std::string> digits = {
        "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
    };
    for (char c = '0'; c <= '9'; ++c) {
        digits.emplace_back(1, c);
    }
    for (std::string s; in >> s; ) {
        std::string::size_type first = s.size();
        std::string::size_type last = 0;
        int first_digit = 0;
        int last_digit = 0;
        for (int i = 0; i < digits.size(); ++i) {
            auto pos = s.find(digits[i]);
            if (pos != std::string::npos) {
                if (pos < first) {
                    first_digit = i % 10;
                    first = pos;
                }
                pos = s.rfind(digits[i]);
                if (last <= pos) {
                    last_digit = i % 10;
                    last = pos;
                }
            }
        }
        ret += 10 * first_digit + last_digit;
    }
    std::cout << ret << '\n';
}