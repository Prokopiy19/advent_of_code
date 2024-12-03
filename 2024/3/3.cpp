#include <charconv>
#include <iostream>
#include <string>
#include <string_view>

// combine all lines in input into 1 line for this program to work

int main() {
    long long gold = 0;
    std::string line;
    std::string pattern = "mul(";
    std::string pattern_do = "do()";
    std::string pattern_dont = "don't()";
    std::string::size_type lastdo;
    std::string::size_type lastdont;
    while (std::getline(std::cin, line)) {
        std::cout << line << std::endl;
        auto pos = line.find(pattern);
        for ( ; pos != std::string::npos; pos = line.find(pattern, pos + 1)) {
            long long lhs = 0;
            auto start = line.c_str() + pos + 4;
            auto result = std::from_chars(start, line.c_str() + line.size(), lhs);
            if (start == result.ptr || *result.ptr != ',') {
                continue;
            }
            long long rhs = 0;
            start = result.ptr + 1;
            result = std::from_chars(start, line.c_str() + line.size(), rhs);
            if (start == result.ptr || *result.ptr != ')') {
                continue;
            }



            std::string_view view{line.c_str(), pos};

            auto ido = view.rfind(pattern_do);
            auto idont = view.rfind(pattern_dont);

            std::cout << pos << ' ' << lhs << ' ' << rhs << " do=" << ido << " don't=" << idont;

            if (idont == std::string::npos || ido != std::string::npos && ido > idont) {
                std::cout << " adding" << std::endl;
                gold += lhs * rhs;
            }
            else {
                std::cout << std::endl;
            }

        }
    }
    std::cout << gold << std::endl;
}