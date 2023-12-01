#include <algorithm>
#include <iostream>
#include <fstream>

#include <ctype.h>

int main()
{
    std::ifstream in("input.txt", std::ios_base::in);
    long long ret = 0;
    for (std::string s; in >> s; ) {
        const char first_digit = *std::find_if(s.cbegin(), s.cend(), isdigit);
        const char last_digit = *std::find_if(s.crbegin(), s.crend(), isdigit);
        ret += 10 * (first_digit - '0') + (last_digit - '0');
    }
    std::cout << ret;
}