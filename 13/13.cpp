#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool hsymmetric(const vector<string>& b, int row)
{
	for (int i = row, j = row + 1; 0 <= i && j < b.size(); --i, ++j)
		if (b[i] != b[j]) {
			return false;
		}
	return true;
}

bool equal_cols(const vector<string>& b, int x, int y)
{
	for (int i = 0; i < b.size(); ++i)
		if (b[i][x] != b[i][y]) {
			return false;
		}
	return true;
}

bool vsymmetric(const vector<string>& b, int col)
{
	for (int i = col, j = col + 1; 0 <= i && j < b[0].size(); --i, ++j)
		if (!equal_cols(b, i, j)) {
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