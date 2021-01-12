#include <bits/stdc++.h>
using namespace std;

int ans(vector<int>& seq) {
    
    int count = 0;

    for (int i = 1; i <= 10; ++i) {
        for (int j = 1; j < 12 - i; ++j) {
            int m = INT_MAX;
            for (int k = j; k < j + i; ++k) {
                m = min(m, seq[k]);
            }
            if (m > seq[j-1] && m > seq[j+i]) ++count;
        }
    }

    return count;

}

int main() {

    int p; cin >> p;
    for (int i = 0; i < p; ++i) {
        int test; cin >> test;
        vector<int> seq(12);
        for (int j = 0; j < 12; ++j) {
            cin >> seq[j];
        }
        cout << test << " " << ans(seq) << '\n';
    }

}