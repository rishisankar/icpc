#include <bits/stdc++.h>
using namespace std;

unsigned long long MOD = 1000000007;

unsigned long long test() {

    int R, C; cin >> R >> C;
    unsigned long long count = 18;

    for (int i = 1; i < R; ++i) {
        count *= 6;
        count %= MOD;
    }

    for (int i = 1; i < C; ++i) {
        count *= 6;
        count %= MOD;
    }

    for (int i = 0; i < (R-1)*(C-1); ++i) {
        count *= 2;
        count %= MOD;
    }

    return count;

}

int main() {

    int T; cin >> T;
    for (int i = 0; i < T; ++i) {
        cout << test() << '\n';
    }

}