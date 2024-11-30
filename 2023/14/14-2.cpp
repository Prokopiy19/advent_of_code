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

void tilt_west()
{
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            if (b[i][j] == 'O') {
                int k = j - 1;
                while (k >= 0 && b[i][k] == '.') {
                    --k;
                }
                ++k;
                swap(b[i][k], b[i][j]);
            }
}

void tilt_south()
{
    for (int i = m - 1; i >= 0; --i)
        for (int j = 0; j < n; ++j)
            if (b[i][j] == 'O') {
                int k = i + 1;
                while (k < m && b[k][j] == '.') {
                    ++k;
                }
                --k;
                swap(b[k][j], b[i][j]);
            }
}

void tilt_east()
{
    for (int i = 0; i < m; ++i)
        for (int j = n - 1; j >= 0; --j)
            if (b[i][j] == 'O') {
                int k = j + 1;
                while (k < n && b[i][k] == '.') {
                    ++k;
                }
                --k;
                swap(b[i][k], b[i][j]);
            }
}

int main()
{
    for (string line; getline(cin, line); ) {
        b.emplace_back(std::move(line));
    }
    m = b.size();
    n = b[0].size();
    
    tilt_north();

    int lim = 1000000000;
    for (int i = 1; i <= lim; ++i) {
        tilt_north();
        tilt_west();
        tilt_south();
        tilt_east();
        
        int load = 0;
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j) {
                load += (b[i][j] == 'O') * (m - i);
            }
        cout << load << ' ' << i << '\n';
    }
}