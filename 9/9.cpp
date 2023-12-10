#include <algorithm>
#include <deque>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    long long part_one = 0;
    long long part_two = 0;
    for (string line; getline(cin, line); ) {
        istringstream in(line);
        vector<deque<int>> nums(1);
        for (int num; in >> num; ) {
            nums[0].emplace_back(num);
        }
        while (any_of(nums.back().cbegin(), nums.back().cend(), [](int e){ return e != 0; })) {
            nums.emplace_back();
            const int prev = nums.size() - 2;
            for(int i = 0; i + 1 < nums[prev].size(); ++i) {
                nums.back().emplace_back(nums[prev][i+1] - nums[prev][i]);
            }
        }
        for (int i = nums.size() - 2; i >= 0; --i) {
            nums[i].emplace_front(nums[i].front() - nums[i+1].front());
            nums[i].emplace_back(nums[i].back() + nums[i+1].back());
        }
        part_one += nums[0].back();
        part_two += nums[0].front();
    }
    cout << part_one << '\n';
    cout << part_two << '\n';
}