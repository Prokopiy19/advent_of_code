#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <vector>

using namespace std;

vector<string> b;
int m, n;

void tilt_north()
{
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            if (b[i][j] == 'O') {
                int k = i - 1;
                while (k >= 0 && b[k][j] == '.') {
                    --k;
                }
                ++k;
                swap(b[k][j], b[i][j]);
            }
}

void print()
{
    for (auto& line : b) {
        cout << line << '\n';
    }
    cout << '\n';
}

int main()
{
    for (string line; getline(cin, line); ) {
        b.emplace_back(std::move(line));
    }
    m = b.size();
    n = b[0].size();

    tilt_north();

    int part_one = 0;
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j) {
            part_one += (b[i][j] == 'O') * (m - i);
        }
    cout << part_one << '\n';

    print();
}