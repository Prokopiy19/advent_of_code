#include <iostream>
#include <string>

int main()
{
    long long ans = 0;
    for (std::string skip; std::cin >> skip; ) {
        long long id;
        std::cin >> id >> skip;

        bool correct = true;
        for (int cnt; std::cin >> cnt; ) {
            std::string color;
            std::cin >> color;
            int max_balls;
            switch (color[0]) {
                case 'r': max_balls = 12; break;
                case 'g': max_balls = 13; break;
                case 'b': max_balls = 14; break;
            }
            correct = correct && cnt <= max_balls;
        }
        std::cin.clear();
        ans += correct ? id : 0;
    }
    std::cout << ans << '\n';
}