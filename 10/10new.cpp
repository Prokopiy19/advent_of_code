#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

using namespace std;
using namespace std::literals;

vector<string> b;
vector<vector<bool>> used;

int m, n;

struct Point{
    int x, y;
};

bool up(char c)
{
	return strchr("|LJ", c);
}

bool down(char c)
{
	return strchr("|7F", c);
}

bool right(char c)
{
	return strchr("-LF", c);
}

bool left(char c)
{
	return strchr("-J7", c);
}

bool connected(int i0, int j0, int i1, int j1)
{
	if (i1 < 0 || m <= i1 || j1 < 0 || n <= j1) {
		return false;
	}
	if (i0 != i1) { // vertical
		if (i0 > i1) {
			swap(i0, i1);
		}
		return down(b[i0][j0]) && up(b[i1][j1]);
	}
	else { // j0 != j1 horizontal
		if (j0 > j1) {
			swap(j0, j1);
		}
		return right(b[i0][j0]) && left(b[i1][j1]);
	}
}

void add_to_queue(queue<Point>& q, int i0, int j0, int i1, int j1)
{
    if (connected(i0, j0, i1, j1) && !used[i1][j1]) {
        used[i1][j1] = true;
        q.emplace(i1, j1);
    }
}

int main()
{
    for (string line; cin >> line; ) {
        b.emplace_back(std::move(line));
    }
    m = b.size();
    n = b[0].size();
    used.resize(m, vector<bool>(n));
	
	queue<Point> q;
	
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < n; ++j)
			if (b[i][j] == 'S') {
				q.emplace(i, j);
				used[i][j] = true;
				for (char c : "|-LJ7F"sv) { // replace S with pipe
					b[i][j] = c;
					int connections = 0;
					connections += connected(i, j, i+1, j);
					connections += connected(i, j, i, j+1);
					connections += connected(i, j, i, j-1);
					connections += connected(i, j, i-1, j);
					if (connections == 2) {
						break;
					}
				}
			}
	int part_one = 1;
	while (!q.empty()) {
		auto [i, j] = q.front();
		q.pop();
		++part_one;
		add_to_queue(q, i, j, i-1, j);
		add_to_queue(q, i, j, i, j-1);
		add_to_queue(q, i, j, i, j+1);
		add_to_queue(q, i, j, i+1, j);
    }
	part_one /= 2;
    cout << part_one << '\n';
	
	int part_two = 0;
	for (int i = 0; i < m; ++i) {
		bool enclosed = false;
		char prev = 0;
		for (int j = 0; j < n; ++j) {
			if (used[i][j]) {
				if (strchr("7FLJ", b[i][j])) {
					if (prev) {
						if (up(prev) && down(b[i][j]) || down(prev) && up(b[i][j])) {
							enclosed = !enclosed;
						}
						prev = 0;
					}
					else {
						prev = b[i][j];
					}
				}
				else if (b[i][j] == '|') {
					enclosed = !enclosed;
				}
			}
			else {
				part_two += enclosed;			
			}
		}
	}
	cout << part_two << '\n';
}