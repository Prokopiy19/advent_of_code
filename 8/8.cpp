#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

unordered_map<string, pair<string, string>> g;
string moves;

int main()
{
    cin >> moves;
    string from, l, r, skip;
    getline(cin, skip);
    getline(cin, skip);
    for (string line; getline(cin, line); ) {
        istringstream sin(line);

        sin >> from >> skip >> l >> r;
        l = l.substr(1, 3);
        r = r.substr(0, 3);
        g[from] = { l, r };
    }

    // string s = "AAA";
    auto curr = moves.cbegin();
    // int part_one = 0;
    // while (s != "ZZZ") {
    //     ++part_one;
    //     switch (*curr) {
    //         case 'L': {
    //             s = g[s].first;
    //             break;
    //         }
    //         case 'R': {
    //             s = g[s].second;
    //             break;
    //         }
    //     }
    //     ++curr;
    //     if (curr == moves.cend()) curr = moves.cbegin();
    // }
    // cout << part_one << endl;

    vector<string> ghosts;
    for (const auto& [from, to] : g) {
        if (from.back() == 'A') ghosts.emplace_back(from);
    }
    int at_finish = 0;
    int part_two = 0;
    vector<int> loops;
    for (auto& ghost : ghosts) {
        curr = moves.cbegin();
        auto s = ghost;
        int loop = 0;
        while (s.back() != 'Z') {
            ++loop;
            switch (*curr) {
                case 'L': {
                    s = g[s].first;
                    break;
                }
                case 'R': {
                    s = g[s].second;
                    break;
                }
            }
            ++curr;
            if (curr == moves.cend()) curr = moves.cbegin();
        }
        cout << loop << ' ';
    }
    cout << endl;
    // while (at_finish < ghosts.size()) {
    //     ++part_two;
    //     switch (*curr) {
    //         case 'L': {
    //             for (auto& ghost : ghosts) {
    //                 if (ghost.back() == 'Z') --at_finish;
    //                 ghost = g[ghost].first;
    //                 if (ghost.back() == 'Z') ++at_finish;
    //             }
    //             break;
    //         }
    //         case 'R': {
    //             for (auto& ghost : ghosts) {
    //                 if (ghost.back() == 'Z') --at_finish;
    //                 ghost = g[ghost].second;
    //                 if (ghost.back() == 'Z') ++at_finish;
    //             }
    //             break;
    //         }
    //     }
    //     ++curr;
    //     if (curr == moves.cend()) curr = moves.cbegin();
    // }
    // cout << part_two << endl;
}