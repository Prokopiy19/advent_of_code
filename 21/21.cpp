#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    constexpr int buf_size = 132;
    char buf0[buf_size][buf_size];
    char buf1[buf_size][buf_size];
    fill_n(&buf0[0][0], buf_size * buf_size, '#');
    fill_n(&buf1[0][0], buf_size * buf_size, '#');
    int m = 0;
    int n;
    {
        string line;
        while (cin >> line) {
            ++m;
            copy(line.cbegin(), line.cend(), &buf0[m][1]);
            copy(line.cbegin(), line.cend(), &buf1[m][1]);
        }
        n = line.size();
    }
    char (*cur)[buf_size] = buf0;
    char (*prv)[buf_size] = buf1;
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            if (cur[i][j] == 'S') {
                cur[i][j] = 'O';
                prv[i][j] = '.';
            }
    for (int steps = 64; steps--; ) {
        swap(cur, prv);
        for (int i = 1; i <= m; ++i)
            for (int j = 1; j <= n; ++j)
                if (cur[i][j] != '#') {
                    if (prv[i-1][j] == 'O' ||
                        prv[i][j-1] == 'O' ||
                        prv[i][j+1] == 'O' ||
                        prv[i+1][j] == 'O')
                    {
                        cur[i][j] = 'O';
                    }
                    else {
                        cur[i][j] = '.';
                    }
                }
    }
    cout << count(&cur[1][0], &cur[buf_size-1][0], 'O') << '\n';
}