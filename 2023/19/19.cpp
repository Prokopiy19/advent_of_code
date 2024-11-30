#include <array>
#include <charconv>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

struct Interval {
    std::array<int, 4> l = {1, 1, 1, 1};
    std::array<int, 4> r = {4000, 4000, 4000, 4000};
};

struct Rule {
    char type;
    int i;
    int val;
    std::string to;
};

bool valid(const Interval& interval)
{
    for (int i = 0; i < 4; ++i)
        if (interval.l[i] > interval.r[i]) {
            return false;
        }
    return true;
}

int main()
{
    std::unordered_map<std::string, std::vector<Rule>> workflows;
    std::string line;
    std::getline(std::cin, line);
    for ( ; line.size() > 1; std::getline(std::cin, line)) {
        for (char& c : line) if (c == '{' || c == '}' || c == ',') c = ' ';
        
        std::istringstream record{line};
        
        std::string s;
        record >> s;
        
        std::vector<Rule> workflow;
        for (std::string t; record >> t; ) {
            auto pos = t.find(':');
            if (pos == std::string::npos) {
                workflow.emplace_back(' ', 0, 0, t);
            }
            else {
                Rule rule;
                switch (t[0]) {
                    case 'x': rule.i = 0; break;
                    case 'm': rule.i = 1; break;
                    case 'a': rule.i = 2; break;
                    case 's': rule.i = 3; break;
                }
                rule.type = t[1];
                std::from_chars(t.c_str() + 2, t.c_str() + pos, rule.val);
                rule.to = t.substr(pos + 1);
                workflow.emplace_back(rule);
            }
        }
        workflows[s] = std::move(workflow);
    }
    long long part_two = 0;
    std::queue<std::pair<std::string, Interval>> q;
    q.emplace("in", Interval{});
    while (!q.empty()) {
        auto [s, interval] = q.front();
        q.pop();
        if (s == "R") {
            continue;
        }
        if (s == "A") {
            long long add = 1;
            for (int i = 0; i < 4; ++i) {
                add *= interval.r[i] - interval.l[i] + 1;
            }
            part_two += add;
        }
        const auto& workflow = workflows[s];
        for (auto rule : workflow) {
            auto new_interval = interval;
            switch (rule.type) {
                case '<': {
                    new_interval.r[rule.i] = rule.val - 1;
                    interval.l[rule.i] = rule.val;
                    break;
                }
                case '>': {
                    new_interval.l[rule.i] = rule.val + 1;
                    interval.r[rule.i] = rule.val;
                    break;
                }
            }
            if (valid(new_interval)) {
                q.emplace(rule.to, new_interval);
            }
        }
    }
    std::cout << part_two << '\n';
}