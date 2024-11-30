#include <algorithm>
#include <iostream>
#include <string>

int main()
{
    long long ans = 0;
    for (std::string skip; std::cin >> skip; ) {
        int id;
        std::cin >> id >> skip;

        long long r = 0, g = 0, b = 0;
        for (long long cnt; std::cin >> cnt; ) {
            std::string color;
            std::cin >> color;
            switch (color[0]) {
                case 'r': r = std::max(r, cnt); break;
                case 'g': g = std::max(g, cnt); break;
                case 'b': b = std::max(b, cnt); break;
            }
        }
        std::cin.clear();
        ans += r * g * b;
    }
    std::cout << ans << '\n';
}