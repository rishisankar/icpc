#include <bits/stdc++.h>
using namespace std;

// COMPILER: GNU C++17	

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        int n, k;
        cin >>n >> k;

        for (int j = 0; j < n; ++j) {
            if (j % 3 == 0) {
                cout << 'a';
            } else if (j % 3 == 1) {
                cout << 'b';
            } else {
                cout << 'c';
            }
        }
        cout << '\n';
    }
}   