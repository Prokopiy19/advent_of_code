#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define int long long

int expand_sum(int sum, int passed, int expanded)
{
    return sum + passed * (expanded - 1);
}

signed main()
{
    vector<string> b;
    for (string line; cin >> line; ) {
        b.emplace_back(std::move(line));
    }
    const int m = b.size();
    const int n = b[0].size();
    vector<bool> empty_rows(m, true), empty_cols(n, true);
    struct Point {
        int r, c;
    };
    vector<Point> g;
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            if (b[i][j] == '#') {
                g.emplace_back(i, j);
                empty_rows[i] = false;
                empty_cols[j] = false;
            }
    int sum = 0;
    int passed = 0;
    for (int i = 0; i < g.size(); ++i)
        for (int j = i + 1; j < g.size(); ++j) {
            sum += abs(g[i].r - g[j].r) + abs(g[i].c - g[j].c);
            int rmin = min(g[i].r, g[j].r);
            int rmax = max(g[i].r, g[j].r);
            int cmin = min(g[i].c, g[j].c);
            int cmax = max(g[i].c, g[j].c);
            for (int r = rmin + 1; r < rmax; ++r) {
                passed += empty_rows[r];
            }
            for (int c = cmin + 1; c < cmax; ++c) {
                passed += empty_cols[c];
            }
        }
    const int part_one = expand_sum(sum, passed, 2);
    cout << part_one << '\n';

    cout << "10 times: " << expand_sum(sum, passed, 10) << '\n';
    cout << "100 times: " << expand_sum(sum, passed, 100) << '\n';

    const int part_two = expand_sum(sum, passed, 1'000'000);
    cout << part_two << '\n';
}