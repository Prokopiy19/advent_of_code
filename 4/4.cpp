#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <unordered_set>

int main()
{
    int i = 0;
    int score = 0;
    int total_cards = 0;
    std::array<int, 300> cards;
    std::fill(cards.begin(), cards.end(), 1);
    for (std::string skip; std::cin >> skip; ++i) {
        std::cin >> skip;
        std::unordered_set<int> wins;
        for (int num; std::cin >> num; ) {
            wins.emplace(num);
        }
        std::cin.clear();
        std::cin >> skip;
        int matches = 0;
        for (int num; std::cin >> num; ) {
            matches += wins.contains(num);
        }
        std::cin.clear();
        score += (matches) ? 1 << (matches - 1) : 0;
        for (int j = i + 1; j <= i + matches; ++j) {
            cards[j] += cards[i];
        }
        total_cards += cards[i];
    }
    std::cout << score << '\n' << total_cards << '\n';
}