#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

constexpr int n = 10;
constexpr int m = 320;

int world[n][n][m];

struct Point {
    int x, y, z;
};

struct Brick {
    Point a, b;
};

void apply_brick_to_world(Brick brick, int value)
{
    for (int x = brick.a.x; x <= brick.b.x; ++x)
    for (int y = brick.a.y; y <= brick.b.y; ++y)
    for (int z = brick.a.z; z <= brick.b.z; ++z) {
        world[x][y][z] = value;
    }
}

bool is_free(Brick brick)
{
    for (int x = brick.a.x; x <= brick.b.x; ++x)
    for (int y = brick.a.y; y <= brick.b.y; ++y)
        if (world[x][y][brick.a.z] >= 0) {
            return false;
        }
    return true;
}

int main()
{
    std::fill_n(&world[0][0][0], n * n * m, -1);
    std::vector<Brick> bricks;
    for (std::string line; std::cin >> line; ) {
        for (char& c : line) if (c == ',' || c == '~') c = ' ';
        std::istringstream record{line};
        
        Point a, b;
        record >> a.x >> a.y >> a.z >> b.x >> b.y >> b.z;
        
        bricks.emplace_back(a, b);
    }
    std::sort(bricks.begin(), bricks.end(), [](auto l, auto r){ return l.a.z < r.a.z; });
    for (int i = 0; i < bricks.size(); ++i) {
        apply_brick_to_world(bricks[i], i);
    }
    for (int i = 0; i < bricks.size(); ++i) {
        apply_brick_to_world(bricks[i], -1);
        while (bricks[i].a.z > 1) {
            --bricks[i].a.z;
            --bricks[i].b.z;
            if (!is_free(bricks[i])) {
                ++bricks[i].a.z;
                ++bricks[i].b.z;
                break;
            }
        }
        apply_brick_to_world(bricks[i], i);
    }
    std::vector<bool> safe_to_destroy(bricks.size(), true);
    std::vector<std::unordered_set<int>> supporters(bricks.size());
    for (int i = 0; i < bricks.size(); ++i) {
        const int z = bricks[i].a.z - 1;
        for (int x = bricks[i].a.x; x <= bricks[i].b.x; ++x)
        for (int y = bricks[i].a.y; y <= bricks[i].b.y; ++y)
            if (world[x][y][z] >= 0) {
                supporters[i].emplace(world[x][y][z]);
            }
        if (supporters[i].size() == 1) {
            safe_to_destroy[*supporters[i].cbegin()] = false;
        }
    }
    
    const int part_one = std::count(safe_to_destroy.cbegin(), safe_to_destroy.cend(), true);
    std::cout << part_one << '\n';
    
    int part_two = 0;
    std::vector<bool> destroyed(bricks.size());
    for (int i = 0; i < bricks.size(); ++i) {
        std::fill(destroyed.begin(), destroyed.end(), false);
        destroyed[i] = true;
        for (int j = i + 1; j < bricks.size(); ++j) {
            if (supporters[j].empty()) {
                continue;
            }
            destroyed[j] = true;
            for (int k : supporters[j])
                if (!destroyed[k]) {
                    destroyed[j] = false;
                    break;
                }
        }
        part_two += std::count(destroyed.cbegin(), destroyed.cend(), true) - 1;
    }
    std::cout << part_two << '\n';
}