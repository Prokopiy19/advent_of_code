#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

struct Module {
    char type;
    vector<string> cables;
    bool on;
    unordered_map<string, bool> mem;
};

struct Pulse {
    bool high;
    string from, to;
};

int cnt_high = 0, cnt_low = 0;

void send_pulses(queue<Pulse>& q, const Module& module, const string& from, bool high)
{
    int& cnt = (high) ? cnt_high : cnt_low;
    for (const auto& to : module.cables) {
        // cout << from << " -" << (high ? "high" : "low") << "-> " << to << '\n';
        ++cnt;
        q.emplace(high, from, to);
    }
}

int main()
{
    unordered_map<string, Module> modules;
    for (string line; getline(cin, line); ) {
        for (char& c : line) if (c == ',') c = ' ';
        istringstream record(line);
        
        string from, skip;
        record >> from >> skip;
        
        Module module;
        module.type = from[0];
        for (string to; record >> to; ) {
            module.cables.emplace_back(std::move(to));
        }
        if (from[0] != 'b') {
            from.erase(from.begin());
        }
        modules[from] = std::move(module);
    }
    for (const auto& [s, input] : modules) {
        for (const auto& to : input.cables) {
            auto& module = modules[to];
            if (module.type == '&') {
                module.mem.emplace(s, false);
            }
        }
    }
    queue<Pulse> q;
    for (int i = 0; i < 1000; ++i) {
        q.emplace(false, "", "broadcaster");
        ++cnt_low;
        while (!q.empty()) {
            auto pulse = q.front();
            q.pop();
            auto& module = modules[pulse.to];
            switch (module.type) {
                case '%': {
                    if (pulse.high == false) {
                        module.on = !module.on;
                        send_pulses(q, module, pulse.to, module.on);
                    }
                    break;
                }
                case '&': {
                    module.mem[pulse.from] = pulse.high;
                    if (all_of(module.mem.cbegin(), module.mem.cend(), [](const auto& e){ return e.second; })) {
                        send_pulses(q, module, pulse.to, false);
                    }
                    else {
                        send_pulses(q, module, pulse.to, true);
                    }
                    break;
                }
                case 'b': {
                    send_pulses(q, module, pulse.to, pulse.high);
                }
            }
        }
    }
    cout << cnt_high << '*' << cnt_low << " = " << cnt_high * 1LL * cnt_low << '\n';
}