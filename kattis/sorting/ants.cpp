#include <bits/stdc++.h>
using namespace std;

int main() {

    int t; cin >> t;
    for (int tests = 0; tests < t; ++tests) {
        int l, n; cin >> l >> n;
        vector<int> pos(n);
        int minpt = INT_MIN;
        int maxpt = INT_MIN;
        for (int i = 0; i < n; ++i) {
            cin >> pos[i];
            minpt = max(minpt, min(pos[i], l - pos[i]));
        }
        sort(pos.begin(), pos.end());

        maxpt = max(max(pos[0], l-pos[0]), max(pos[n-1],l-pos[n-1]));
        cout << minpt << ' ' << maxpt << '\n';
    } 

}