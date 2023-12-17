#include <array>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

enum Dir {
    UP, LEFT, DOWN, RIGHT,
};

using Cell = array<array<int, 11>, 4>;

struct QueueEntry {
    int dist;
    int r, c;
    int dir;
    int moves;
};

bool operator<(QueueEntry lhs, QueueEntry rhs)
{
    return lhs.dist > rhs.dist;
}

int dr(int dir)
{
    switch (dir) {
        case UP: return -1;
        case DOWN: return 1;
    }
    return 0;
}

int dc(int dir)
{
    switch (dir) {
        case LEFT: return -1;
        case RIGHT: return 1;
    }
    return 0;
}

int main()
{
    vector<vector<int>> b;
    for (string line; cin >> line; ) {
        b.emplace_back();
        for (char c : line) {
            b.back().emplace_back(c-'0');
        }
    }
    const int m = b.size();
    const int n = b[0].size();
    vector<vector<Cell>> dp(m, vector<Cell>(n));
    for (auto& row : dp)
        for (auto& cell : row)
            for (auto& dir : cell) {
                fill(dir.begin(), dir.end(), INT_MAX);
            }
    priority_queue<QueueEntry> q;
    q.emplace(-b[0][0], 0, 0, DOWN, 10);
    q.emplace(-b[0][0], 0, 0, RIGHT, 10);
    while (q.empty() == false) {
        auto [dist, r, c, dir, moves] = q.top();
        q.pop();
        if (r < 0 || m <= r || c < 0 || n <= c || dp[r][c][dir][moves] <= dist + b[r][c]) {
            continue;
        }
        dist += b[r][c];
        dp[r][c][dir][moves] = dist;
        if (moves > 0) {
            q.emplace(dist, r + dr(dir), c + dc(dir), dir, moves-1);
        }
        if (moves <= 6)
            for (int i = 0; i < 4; ++i)
                if (i != dir && abs(i - dir) != 2) {
                    q.emplace(dist, r + dr(i), c + dc(i), i, 9);
                }
    }
    const auto& finish = dp.back().back();
    int part_two = INT_MAX;
    for (const auto& dir : finish) {
        for (int i = 0; i <= 6; ++i) {
            part_two = min(part_two, dir[i]);
        }
    }
    cout << part_two;
}