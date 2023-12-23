#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

constexpr int buf_size = 143;
char b[buf_size][buf_size];
std::array<std::bitset<buf_size>, buf_size> used;
int m = 0, n = 0;
int ans = INT_MIN;

struct Coord {
    int i, j;
} start, finish;

inline
bool operator<(Coord lhs, Coord rhs)
{
    return lhs.i < rhs.i || lhs.i == rhs.i && lhs.j < rhs.j;
}

inline
bool operator==(Coord lhs, Coord rhs)
{
    return lhs.i == rhs.i && lhs.j == rhs.j;
}

inline
bool operator!=(Coord lhs, Coord rhs)
{
    return !(lhs == rhs);
}

std::map<Coord, std::map<Coord, int>> g;

bool is_vertex(int i, int j)
{
    if (b[i][j] == '#') {
        return false;
    }
    if (i == 1 || i == m) {
        return true;
    }
    int paths = 0;
    paths += (b[i-1][j] != '#');
    paths += (b[i][j-1] != '#');
    paths += (b[i][j+1] != '#');
    paths += (b[i+1][j] != '#');
    return paths >= 3;
}

inline
bool is_vertex(Coord coord)
{
    return is_vertex(coord.i, coord.j);
}

std::vector<Coord> get_adjacent_list(Coord coord)
{
    std::vector<Coord> ret;
    auto [i, j] = coord;
    if (b[i-1][j] == '.') ret.emplace_back(i-1, j);
    if (b[i][j-1] == '.') ret.emplace_back(i, j-1);
    if (b[i][j+1] == '.') ret.emplace_back(i, j+1);
    if (b[i+1][j] == '.') ret.emplace_back(i+1, j);
    return ret;
}

void dfs(int i, int j, int dist)
{
    if (b[i][j] == '#' || used[i][j] == true) {
        return;
    }
    if (i == m) {
        if (dist > ans) {
            std::cout << dist << '\n';
        }
        ans = std::max(ans, dist);
        return;
    }
    used[i][j] = true;
    switch(b[i][j]) {
        case '.': {
            dfs(i - 1, j, dist + 1);
            dfs(i, j - 1, dist + 1);
            dfs(i, j + 1, dist + 1);
            dfs(i + 1, j, dist + 1);
            break;
        }
        case '^': dfs(i - 1, j, dist + 1); break;
        case '<': dfs(i, j - 1, dist + 1); break;
        case '>': dfs(i, j + 1, dist + 1); break;
        case 'v': dfs(i + 1, j, dist + 1); break;
    }
    used[i][j] = false;
}

std::pair<Coord, int> find_vertex(Coord cur, Coord from, int dist)
{
    if (is_vertex(cur)) {
        return {cur, dist};
    }
    for (auto coord : get_adjacent_list(cur))
        if (coord != from) {
            return find_vertex(coord, cur, dist + 1);
        }
    return {};
}

inline
std::ostream& operator<<(std::ostream& os, Coord coord)
{
    os << coord.i << ' ' << coord.j;
    return os;
}

std::set<Coord> vis;
void dfs2(Coord coord, int dist)
{
    if (coord == finish) {
        if (dist > ans) {
            std::cout << dist << '\n';
        }
        ans = std::max(ans, dist);
        return;
    }
    if (vis.contains(coord)) {
        return;
    }
    vis.emplace(coord);
    for (auto& [to, steps] : g[coord]) {
        dfs2(to, dist + steps);
    }
    vis.erase(coord);
}

int main()
{
    std::fill_n(&b[0][0], buf_size * buf_size, '#');
    {
        std::string line;
        while (std::cin >> line) {
            ++m;
            std::copy(line.cbegin(), line.cend(), &b[m][1]);
        }
        n = line.size();
    }
    std::cout << m << ' ' << n << '\n';
    for (int j = 1; j <= n; ++j) {
        dfs(1, j, 0);
    }
    int part_one = ans;
    std::cout << "part one: " << part_one << '\n';
    
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            if (b[i][j] != '.' && b[i][j] != '#') b[i][j] = '.';
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            if (is_vertex(i, j)) {
                Coord coord{i, j};
                for (auto tmp : get_adjacent_list(coord)) {
                    auto [v, steps] = find_vertex(tmp, coord, 1);
                    g[coord][v] = steps;
                    g[v][coord] = steps;
                }
            }
    for (auto& [v, ulist] : g) {
        std::cout << v << ":";
        for (auto& [to, steps] : ulist) {
            std::cout << " " << to << "(" << steps << ")";
        }
        std::cout << '\n';
    }
    
    for(int j = 1; j <= n; ++j) {
        if (b[1][j] == '.') {
            start = { 1, j };
        }
        if (b[m][j] == '.') {
            finish = { m, j };
        }
    }
    std::cout << "start: " << start << '\n';
    std::cout << "finish: " << finish << '\n';
    ans = INT_MIN;
    std::cout << "graph size: " << g.size() << '\n';
    dfs2(start, 0);
    const int part_two = ans;
    std::cout << part_two << '\n';
    
}