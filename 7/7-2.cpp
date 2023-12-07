#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <string_view>
#include <utility>
#include <vector>

using namespace std;

enum HandType {
    high, one, two, three, full, four, five,
};

HandType hand_type(const string_view s) {
    map<char, int> cnts;
    for (char c : s) {
        ++cnts[c];
    }
    if (auto it = cnts.find('1'); it != cnts.end()) {
        int jcnt = it->second;
        if (jcnt == 5) return five;
        cnts.erase(it);
        auto max_it = cnts.begin();
        for (it = cnts.begin(); it != cnts.end(); ++it)
            if (it->second > max_it->second) max_it = it;
        max_it->second += jcnt;
    }
    switch (cnts.size()) {
        case 1: return five;
        case 2: {
            int cnt = cnts.begin()->second;
            if (cnt == 1 || cnt == 4) return four;
            else return full;
        }
        case 3: {
            int max_cnt = 0;
            for (auto [c, cnt] : cnts) max_cnt = max(max_cnt, cnt);
            if (max_cnt == 3) return three;
            else return two;
        }
        case 4: return one;
        case 5: return high;
    }
    return high;
}

bool cmp(const string_view lhs, const string_view rhs)
{
    auto ltype = hand_type(lhs);
    auto rtype = hand_type(rhs);
    return ltype < rtype || ltype == rtype && lhs < rhs;
}

int main()
{
    vector<pair<string, long long>> hands;
    for (string hand; cin >> hand; ) {
        long long bid;
        cin >> bid;
        for (char& c : hand) {
            switch(c) {
                case 'J': c = '1'; break;
                case 'T': c = '9' + 1; break;
                case 'Q': c = '9' + 2; break;
                case 'K': c = '9' + 3; break;
                case 'A': c = '9' + 4; break;
            }
        }
        hands.emplace_back(hand, bid);
    }
    sort(hands.begin(), hands.end(), [](auto& lhs, auto& rhs){ return cmp(lhs.first, rhs.first); });
    long long part_two = 0;
    for (long long i = 0; i < hands.size(); ++i) {
        part_two += (i + 1) * hands[i].second;
    }
    std::cout << part_two << '\n';
}