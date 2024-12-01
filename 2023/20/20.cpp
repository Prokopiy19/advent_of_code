#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

struct Pulse {
    enum Type {
        kLow, kHigh,
    } type;
    string from, to;
};

struct Module {
    char type = 'a';
    vector<string> cables;
    bool on = false;
    unordered_map<string, Pulse::Type> mem;
    int high_count = 0;
};

unsigned long long cnt_high = 0, cnt_low = 0;

void send_pulses(queue<Pulse>& q, const Module& module, const string& from, Pulse::Type type)
{
    auto& cnt = (type == Pulse::kHigh) ? cnt_high : cnt_low;
    for (const auto& to : module.cables) {
        // cout << from << " -" << (high ? "high" : "low") << "-> " << to << '\n';
        ++cnt;
        q.emplace(type, from, to);
    }
}

string enclose(string name) {
    return '"' + name + '"';
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
                module.mem.emplace(s, Pulse::kLow);
            }
        }
    }
    map<string, vector<int>> tracking {
        {"pm", {}},
        {"mk", {}},
        {"pk", {}},
        {"hf", {}},
    };
    queue<Pulse> q;
    for (int i = 0; i < 200; ++i) {
        q.emplace(Pulse::kLow, "", "broadcaster");
        ++cnt_low;
        while (!q.empty()) {
            auto pulse = q.front();
            q.pop();
            auto& module = modules[pulse.to];
            switch (module.type) {
                case '%': {
                    if (pulse.type == Pulse::kLow) {
                        module.on = !module.on;
                        send_pulses(q, module, pulse.to, (module.on) ? Pulse::kHigh : Pulse::kLow);
                    }
                    break;
                }
                case '&': {
                    auto itmem = module.mem.find(pulse.from);
                    if (itmem->second != pulse.type) {
                        if (pulse.type == Pulse::kHigh) {
                            ++module.high_count;
                        }
                        else {
                            --module.high_count;
                        }
                        itmem->second = pulse.type;
                    }
                    if (module.high_count == module.mem.size()) {
                        send_pulses(q, module, pulse.to, Pulse::kLow);
                    }
                    else {
                        send_pulses(q, module, pulse.to, Pulse::kHigh);
                    }
                    break;
                }
                case 'b': {
                    send_pulses(q, module, pulse.to, pulse.type);
                    break;
                }
            }
        }

        for (auto &[name, vec] : tracking) {
            if (modules[name].on) {
                std::cout << name << ' ' << i << std::endl;
                vec.emplace_back(i);
            }
        }
        for (auto [name, signal] : modules["cz"].mem) {
            if (signal == Pulse::kHigh) {
                std::cout << '1';
            }
            else {
                std::cout << '0';
            }
        }
        std::cout << std::endl;
    }
    cout << cnt_high << '*' << cnt_low << " = " << cnt_high * cnt_low << '\n';

    for (auto &[name, vec] : tracking) {
        std::cout << name;
        for (auto i : vec) {
            std::cout << ' ' << i;
        }
        std::cout << '\n';
    }

    std::ofstream file{"output.txt"};
    file << "digraph mygraph {\n";

    //nodes
    for (auto &[name, module] : modules) {
        file << enclose(name) << '\n';
    }

    // vertices
    for (auto &[name, module] : modules)
        for (auto to : module.cables) {
            file << enclose(name) << " -> " << enclose(to) << std::endl;
        }

    file << "}" << std::endl;
}