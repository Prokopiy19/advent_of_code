#include <algorithm>
#include <array>
#include <bitset>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <utility>

struct Greater1st {
    bool operator()(std::pair<int, int> lhs, std::pair<int, int> rhs) const noexcept
    {
        return lhs.first > rhs.first;
    }
};

int main()
{
    int i = 0;
    int score = 0;
    int total_cards = 0;
    int cards = 1;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, Greater1st> decrease;
    decrease.emplace(INT_MAX, 0);
    for (std::string skip; std::cin >> skip; ++i) {
        std::cin >> skip;
        std::bitset<100> wins;
        for (int num; std::cin >> num; ) {
            wins[num] = true;
        }
        std::cin.clear();
        std::cin >> skip;
        int matches = 0;
        for (int num; std::cin >> num; ) {
            matches += wins[num];
        }
        std::cin.clear();
        score += (matches) ? 1 << (matches - 1) : 0;
        const int current_cards = cards;
        total_cards += current_cards;
        if (matches) {
            cards += current_cards;
            decrease.emplace(i + matches, current_cards);
        }
        while (i == decrease.top().first) {
            cards -= decrease.top().second;
            decrease.pop();
        }
    }
    std::cout << score << '\n' << total_cards << '\n';
}