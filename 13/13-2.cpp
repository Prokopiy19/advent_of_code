#include <iostream>
#include <string>
#include <vector>

using namespace std;

int mismatch_rows(const vector<string>& b, int x, int y)
{
	int ret = 0;
	for (int j = 0; j < b[x].size(); ++j)
		ret += (b[x][j] != b[y][j]);
	return ret;
}

int mismatch_cols(const vector<string>& b, int x, int y)
{
	int ret = 0;
	for (int i = 0; i < b.size(); ++i)
		ret += (b[i][x] != b[i][y]);
	return ret;
}

bool hsymmetric(const vector<string>& b, int row)
{
	int m = 0;
	for (int i = row, j = row + 1; 0 <= i && j < b.size(); --i, ++j) {
		m += mismatch_rows(b, i, j);
	}
	if (m != 1) {
		return false;
	}
	return true;
}

bool vsymmetric(const vector<string>& b, int col)
{
	int m = 0;
	for (int i = col, j = col + 1; 0 <= i && j < b[0].size(); --i, ++j) {
		m += mismatch_cols(b, i, j);
	}
	if (m != 1) {
		return false;
	}
	return true;
}

int main()
{
	int part_one = 0;
	for (string line; getline(cin, line); ) {
		vector<string> b;
		for ( ; !line.empty(); getline(cin, line)) {
			b.emplace_back(std::move(line));
		}
		for (int i = 0; i + 1 < b.size(); ++i)
			if (hsymmetric(b, i)) {
				part_one += 100 * (i + 1);
			}
		for (int j = 0; j + 1 < b[0].size(); ++j)
			if (vsymmetric(b, j)) {
				part_one += j + 1;
			}
	}
	cout << part_one << '\n';
}