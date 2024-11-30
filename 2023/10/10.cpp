#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;

vector<string> b;
vector<vector<bool>> used;

int m, n;
int si, sj;

void build_map(istream& in)
{
    vector<string> minimap;
    for (string line; in >> line; ) {
        minimap.emplace_back(std::move(line));
    }
    m = 3 * minimap.size();
    n = 3 * minimap[0].size();
    b.resize(m, string(n, '.'));
    used.resize(m, vector<bool>(n));
    for (int i = 0; i < m; i += 3)
        for (int j = 0; j < n; j += 3) {
            switch (minimap[i/3][j/3]) {
                case '|': {
                    b[i  ][j+1] = '#';
                    b[i+1][j+1] = '#';
                    b[i+2][j+1] = '#';
                    break;
                }
                case '-': {
                    b[i+1][j  ] = '#';
                    b[i+1][j+1] = '#';
                    b[i+1][j+2] = '#';
                    break;
                }
                case 'L': {
                    b[i  ][j+1] = '#';
                    b[i+1][j+1] = '#';
                    b[i+1][j+2] = '#';
                    break;
                }
                case 'J': {
                    b[i  ][j+1] = '#';
                    b[i+1][j+1] = '#';
                    b[i+1][j  ] = '#';
                    break;
                }
                case '7': {
                    b[i+1][j  ] = '#';
                    b[i+1][j+1] = '#';
                    b[i+2][j+1] = '#';
                    break;
                }
                case 'F': {
                    b[i+1][j+2] = '#';
                    b[i+1][j+1] = '#';
                    b[i+2][j+1] = '#';
                    break;
                }
                case 'S': {
                    si = i+1;
                    sj = j+1;
                    b[i+1][j+1] = '#';
                    b[i  ][j+1] = '#';
                    b[i+2][j+1] = '#';
                    b[i+1][j  ] = '#';
                    b[i+1][j+2] = '#';
                }
            }
        }
}

struct Point{
    int x, y;
};

void add_to_queue(queue<Point>& q, int i, int j, bool in_pipes, int& counter)
{
    if (i < 0 || m <= i || j < 0 || n <= j) {
        if (!in_pipes) {
            counter = INT_MIN;
        }
        return;
    }
    if (!used[i][j] && (!in_pipes || b[i][j] == '#')) {
        used[i][j] = true;
        q.emplace(i, j);
    }
}

int bfs(int i, int j, bool in_pipes)
{
    if (used[i][j]) {
        return 0;
    }
    used[i][j] = true;
    int ret = 0;
    queue<Point> q;
    q.emplace(i, j);
    while (!q.empty()) {
        int k = q.size();
        while (k--) {
            auto [i, j] = q.front();
            q.pop();
            if (i%3 == 1 && j%3 == 1) {
                ++ret;
            }
            add_to_queue(q, i-1, j, in_pipes, ret);
            add_to_queue(q, i, j-1, in_pipes, ret);
            add_to_queue(q, i, j+1, in_pipes, ret);
            add_to_queue(q, i+1, j, in_pipes, ret);
        }
    }
    return ret;
}

int main()
{
    build_map(cin);
    const int part_one = bfs(si, sj, true) / 2;
    cout << part_one << '\n';
    int part_two = 0;
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j) {
            const int area = bfs(i, j, false);
            if (area > 0) {
                part_two += area;
            }
        }
    cout << part_two << '\n';
}