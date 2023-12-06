#include <iostream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

long long solve(const long long time, const long long dist)
{
    auto discr = time*time - 4*dist;
    if (discr < 0) {
        return 0;
    }
    long long max_v = 0.5 * (time + sqrt(discr));
    long long min_v = ceil(0.5 * (time - sqrt(discr)));
    return max_v - min_v + 1;
}

long long concat(const vector<int>& v)
{
    string ret;
    for (const int num : v) {
        ret += to_string(num);
    }
    return stoll(ret);
}

int main()
{
    string skip;
    cin >> skip;
    
    vector<int> times;
    for (int t; cin >> t; ) {
        times.emplace_back(t);
    }
    cin.clear();
    cin >> skip;
    vector<int> distances;
    for (int d; cin >> d; ) {
        distances.emplace_back(d);
    }

    int part_one = 1;
    for (int i = 0; i < times.size(); ++i) {
        part_one *= solve(times[i], distances[i]);
    }
    cout << part_one << '\n';

    long long part_two = solve(concat(times), concat(distances));
    cout << part_two << '\n';
}