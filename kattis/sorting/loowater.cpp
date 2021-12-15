#include <bits/stdc++.h>
using namespace std;

int main() {
    while (true) {
        int n, m;
        cin >> n >> m;
        if (n == 0 && m == 0) break;

        vector<int> heads(n);
        vector<int> knights(m);
        for (int i = 0; i < n; ++i) {
            cin >> heads[i];
        }
        for (int i = 0; i < m; ++i) {
            cin >> knights[i];
        }
        sort(heads.begin(), heads.end());
        sort(knights.begin(), knights.end());

        int count = 0;
        int k = 0;
        for (int h = 0; h < heads.size(); ++h) {
            while (k < knights.size() && knights[k] < heads[h]) {
                ++k;
            }
            if (k < knights.size()) {
                count += knights[k];
                ++k;
            } else {
                count = -1;
                break;
            }
        }
        if (count == -1) {
            cout << "Loowater is doomed!\n";
        } else {
            cout << count << '\n';
        }
    }
}