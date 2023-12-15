#include <algorithm>
#include <array>
#include <charconv>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int box_id(const string_view s)
{
    int h = 0;
    for (const char c : s) {
        h += c;
        h *= 17;
        h %= 256;
    }
    return h;
}

void print(const array<vector<pair<string, int>>, 256>& boxes)
{
    for (int i = 0; i < boxes.size(); ++i) {
        if (boxes[i].empty()) continue;
        cout << "Box " << i << ':';
        for (const auto& [s, l] : boxes[i]) {
            cout << " [" << s << ' ' << l << ']';
        }
        cout << '\n';
    }
    cout << '\n';
}

int main()
{
    array<vector<pair<string, int>>, 256> boxes;
    string line;
    getline(cin, line);
    for (char& c : line) if (c == ',') c = ' ';
    istringstream record(line);
    for (string s; record >> s; ) {
        if (s.back() == '-') {
            s.pop_back();
            auto& box = boxes[box_id(s)];
            auto it = find_if(box.begin(), box.end(), [&s](const auto& p){ return p.first == s; });
            if (it != box.end()) box.erase(it);
        }
        else {
            auto pos = s.find('=');
            int lens;
            from_chars(s.data() + pos + 1, s.data() + s.size(), lens);
            s.resize(pos);
            auto& box = boxes[box_id(s)];
            auto it = find_if(box.begin(), box.end(), [&s](const auto& p){ return p.first == s; });
            if (it != box.end()) {
                it->second = lens;
            }
            else {
                box.emplace_back(s, lens);
            }
        }
    }
    int part_two = 0;
    for (int i = 0; i < boxes.size(); ++i)
        for (int j = 0; j < boxes[i].size(); ++j) {
            part_two += (i+1) * (j+1) * boxes[i][j].second;
        }
    cout << part_two << '\n';
}