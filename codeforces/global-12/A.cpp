#include <bits/stdc++.h>
using namespace std;

// COMPILER: GNU C++17	

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        int n;
        cin >>n;

        string s;
        cin >> s;

        int count = 0;
        for (int j = 0; j < n; ++j) {
            if (s.at(j) == 'b') {
                count++;
            }
        }

        for (int j = 0; j < count; ++j) {
            cout << 'b';
        }
        for (int j = 0; j < n; ++j) {
            if (s.at(j) != 'b') {
                cout << s.at(j);
            }
        }

        cout << '\n';
    }
}   