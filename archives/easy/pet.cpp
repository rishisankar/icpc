#include <bits/stdc++.h>
using namespace std;

int main() {
    int b, m = INT_MIN;
    for (int i = 1; i <= 5; ++i) {
        int s = 0; int tmp;
        for (int j = 1; j <= 4; ++j) { cin >> tmp; s += tmp; }
        if (s > m) {
            b = i;
            m = s;
        }
    }
    cout << b << " " << m << '\n';
}