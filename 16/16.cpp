#include <bitset>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

struct Ray {
    int r, c;
    int dr=0, dc=0;
};

inline
int dir(Ray ray)
{
    ray.dr = (ray.dr < 0) ? 2 : ray.dr;
    ray.dc = (ray.dc < 0) ? 2 : ray.dc;
    return 3 * ray.dr + ray.dc;
}

int solve(const vector<string>& b, int r, int c, int dr, int dc)
{
    const int m = b.size();
    const int n = b[0].size();
    vector<vector<bitset<9>>> used(m, vector<bitset<9>>(n));
    queue<Ray> rays;
    rays.emplace(r, c, dr, dc);
    while (rays.empty() == false) {
        auto ray = rays.front();
        rays.pop();
        if (ray.r < 0 || m <= ray.r || ray.c < 0 || n <= ray.c || used[ray.r][ray.c][dir(ray)]) {
            continue;
        }
        used[ray.r][ray.c][dir(ray)] = true;
        switch(b[ray.r][ray.c]) {
            case '.': break;
            case '/': ray = Ray{ray.r, ray.c, -ray.dc, -ray.dr}; break;
            case '\\': ray = Ray{ray.r, ray.c, ray.dc, ray.dr}; break;
            case '|': {
                if (ray.dc == 0) break;
                rays.emplace(ray.r, ray.c, 1, 0);
                rays.emplace(ray.r, ray.c, -1, 0);
                continue;
            }
            case '-': {
                if (ray.dr == 0) break;
                rays.emplace(ray.r, ray.c, 0, 1);
                rays.emplace(ray.r, ray.c, 0, -1);
                continue;
            }
        }
        ray.r += ray.dr;
        ray.c += ray.dc;
        rays.emplace(ray);
    }
    int ret = 0;
    for (const auto& v : used) {
        for (const auto& b : v)
            ret += b.any();
    }
    return ret;
}

int main()
{
    vector<string> b;
    for (string line; cin >> line; ) {
        b.emplace_back(std::move(line));
    }
    const int m = b.size();
    const int n = b[0].size();

    int part_one = solve(b, 0, 0, 0, 1);
    cout << part_one << '\n';
    int part_two = 0;
    for (int r = 0; r < m; ++r) {
        part_two = max(part_two, solve(b, r,   0, 0,  1));
        part_two = max(part_two, solve(b, r, n-1, 0, -1));
    }
    for (int c = 0; c < n; ++c) {
        part_two = max(part_two, solve(b,   0, c,  1, 0));
        part_two = max(part_two, solve(b, m-1, c, -1, 0));
    }
    cout << part_two << '\n';
}