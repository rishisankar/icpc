#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, p;
    cin >> n >> p;
    vector<bool> bits(n+1, false);
    vector<bool> allowed(n+1, false);

    allowed[0] = allowed[n] = true;
    for (int i = 0; i < p; ++i) {
        int tmp; cin >> tmp;
        allowed[tmp] = true;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j <=n; ++j) {
            if (allowed[i] && allowed[j]) {
                bits[j-i] = true;
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (bits[i]) cout << i << ' ';
    }
    cout << '\n';

}