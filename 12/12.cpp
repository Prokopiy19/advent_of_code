#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#define int long long

inline
bool operational(char c)
{
	return c == '.' || c == '?';
}

inline
bool damaged(char c)
{
	return c == '#' || c == '?';
}

int solve(string s, const vector<int>& nums)
{
	s = '.' + s + '.';
	auto first = s.find('#');
	first = (first == string::npos) ? s.size() : first;
	vector<int> curr(s.size()), prev(s.size());
	fill(curr.begin(), curr.begin() + first, 1);
	for (int i = 0; i < nums.size(); ++i) {
		swap(curr, prev);
		fill(curr.begin(), curr.end(), 0);
		for (int j = 0; j + nums[i] < s.size(); ++j)
			if (all_of(s.begin() + j, s.begin() + j + nums[i], damaged))
				for (int k = j+nums[i]; k < s.size() && operational(s[k]); ++k)
					curr[k] += prev[j-1];
	}
	return curr.back();
}

signed main()
{
	int part_one = 0;
	int part_two = 0;
	for (string line; getline(cin, line); ) {
		for (char& c : line) if (c == ',') c = ' ';
		istringstream record(line);
		
		string s;
		record >> s;
		vector<int> nums;
		for (int num; record >> num; ) {
			nums.emplace_back(num);
		}
		part_one += solve(s, nums);
		string s5;
		vector<int> nums5;
		for (int i = 0; i < 5; ++i) {
			s5 += s + '?';
			nums5.insert(nums5.end(), nums.cbegin(), nums.cend());
		}
		s5.pop_back();
		part_two += solve(s5, nums5);
	}
	cout << part_one << '\n';
	cout << part_two << '\n';
}