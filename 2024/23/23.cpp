#include <algorithm>
#include <bit>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

int main() {
    std::unordered_map<std::string, std::set<std::string>> g;
    std::unordered_set<std::string> vertices;
    std::string line;
    for (int i = 0; std::getline(std::cin, line); ++i) {
        line[2] = ' ';
        std::istringstream record{line};
        std::string v, u;
        record >> v >> u;
        g[v].emplace(u);
        g[u].emplace(v);
        vertices.emplace(v);
        vertices.emplace(u);
    }
    int silver = 0;

    for (auto it0 = vertices.cbegin(); it0 != vertices.cend(); ++it0) {
        for (auto it1 = next(it0); it1 != vertices.cend(); ++it1) {
            if (g[*it0].contains(*it1)) {
                for (auto it2 = next(it1); it2 != vertices.cend(); ++it2) {
                    if (g[*it0].contains(*it2) && g[*it1].contains(*it2) &&
                            ((*it0)[0] == 't' || (*it1)[0] == 't' || (*it2)[0] == 't')) {
                        ++silver;
                    }
                }
            }
        }
    }
    std::cout << silver << '\n';

    std::vector<std::string> gold;
    for (const auto &v : vertices) {
        const unsigned lim = 1 << g[v].size();
        for (unsigned mask = 0; mask < lim; ++mask) {
            if (std::popcount(mask) + 1 <= gold.size()) {
                continue;
            }
            std::vector<std::string> component{v};
            unsigned bit = 1;
            for (const auto &u : g[v]) {
                if (mask & bit) {
                    component.emplace_back(u);
                }
                bit <<= 1;
            }
            bool correct = true;
            for (int i = 0; i < component.size(); ++i) {
                for (int j = i + 1; j < component.size(); ++j) {
                    if (!g[component[i]].contains(component[j])) {
                        correct = false;
                        break;
                    }
                }
                if (!correct) {
                    break;
                }
            }
            if (correct) {
                gold = std::move(component);
            }
        }
    }
    std::sort(gold.begin(), gold.end());
    for (const auto &s : gold) {
        std::cout << s << ',';
    }
}