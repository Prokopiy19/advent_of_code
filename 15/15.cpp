#include <iostream>
#include <string>
#include <sstream>

using namespace std;


int main()
{
    string line;
    getline(cin, line);
    for (char& c : line) if (c == ',') c = ' ';
    istringstream record(line);
    int part_one = 0;
    for (string s; record >> s; ) {
        int h = 0;
        for (char c : s) {
            h += c;
            h *= 17;
            h %= 256;
        }
        part_one += h;
    }
    cout << part_one << '\n';
}