#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#define int long long
#define l first
#define r second

struct Range {
    int to, from, size;
};

signed main()
{
    std::ifstream in("input.txt");
    
    std::string skip;
    in >> skip;

    std::vector<int> seeds;
    for (int seed; in >> seed; ) {
        seeds.emplace_back(seed);
    }
    in.clear();
    
    std::vector< std::vector<Range> > maps;
    while (in >> skip >> skip) {
        std::vector<Range> ranges;
        for (Range range; in >> range.to >> range.from >> range.size; ) {
            ranges.emplace_back(range);
        }
        in.clear();
        maps.emplace_back(std::move(ranges));
    }

    int part_one = LLONG_MAX;
    for (const int seed : seeds) {
        int x = seed;
        for (const auto& ranges : maps)
            for (const auto range : ranges)
                if (range.from <= x && x < range.from + range.size) {
                    x = range.to + (x - range.from);
                    break;
                }
        part_one = std::min(part_one, x);
    }
    std::cout << part_one << '\n';

    std::deque< std::pair<int, int> > seed_ranges;
    while (!seeds.empty()) {
        seed_ranges.emplace_back(seeds[seeds.size() - 2], seeds[seeds.size() - 2] + seeds.back() - 1);
        seeds.resize(seeds.size() - 2);
    }
    for (const auto& ranges : maps) {
        std::deque< std::pair<int, int> > new_ranges;
        for (const auto range : ranges) {
            std::pair<int, int> from_range = { range.from, range.from + range.size - 1 };
            for (int n = seed_ranges.size(); n--; ) {
                auto seed_range = seed_ranges.front();
                seed_ranges.pop_front();
                // Hardest part here: handle 4 range overlap cases
                if (from_range.l <= seed_range.l && seed_range.r <= from_range.r) {
                    new_ranges.emplace_back(range.to + (seed_range.l - range.from), range.to + (seed_range.r - range.from));
                }
                else if (seed_range.l <= from_range.l && from_range.r <= seed_range.r) {
                    new_ranges.emplace_back(range.to, range.to + range.size - 1);
                    if (seed_range.l < from_range.l) {
                        seed_ranges.emplace_back(seed_range.l, from_range.l - 1);
                    }
                    if (from_range.r < seed_range.r) {
                        seed_ranges.emplace_back(from_range.r + 1, seed_range.r);
                    }
                }
                else if (seed_range.l <= from_range.l && from_range.l <= seed_range.r) {
                    new_ranges.emplace_back(range.to, range.to + (seed_range.r - range.from));
                    if (seed_range.l < from_range.l) {
                        seed_ranges.emplace_back(seed_range.l, from_range.l - 1);
                    }
                }
                else if (seed_range.l <= from_range.r && from_range.r <= seed_range.r) {
                    new_ranges.emplace_back(range.to + (seed_range.l - range.from), range.to + range.size - 1);
                    if (from_range.r < seed_range.r) {
                        seed_ranges.emplace_back(from_range.r + 1, seed_range.r);
                    }
                }
                else {
                    seed_ranges.emplace_back(seed_range);
                }
            }
        }
        seed_ranges.insert(seed_ranges.end(), new_ranges.cbegin(), new_ranges.cend());
    }
    int part_two = LLONG_MAX;
    for (const auto range : seed_ranges) {
        part_two = std::min(part_two, range.l);
    }
    std::cout << part_two << '\n';
}