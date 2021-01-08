#include <bits/stdc++.h>
using namespace std;

// COMPILER: GNU C++17	

int main() {
    int t;
    cin >> t;
    cout.setf(ios::fixed);
    cout.precision(10);
    for (int i = 0; i < t; ++i) {
        int n, m;
        cin >> n >> m;

        vector<int> vec(n);
        for (int j = 0; j < n; ++j) {
            cin >> vec[j];
        }

        int j;
        for (j = n - 1; j >= 0; --j) {
            if (vec[j] != j + 1) {
                break;
            }
        }
        ++j;

        if (j <= 0) {

            for (int k = 0; k < m; ++k) {
                int trash; long double trash2;
                cin >> trash >> trash2;
            }

            cout << 1.0 << '\n';
            continue;
        }

        long double prob = 0.0;

        for (int k = 0; k < m; ++k) {
            int num;
            long double p;

            cin >> num >> p;

            if (num >= j) {
                prob += (1-prob) * p;
            }
        }

        sort(vec.begin(), vec.end());
        bool success = true;
        for (int k = 0; k < n; ++k) {
            if (vec[k] != k + 1) {
                success = false;
                break;
            }
        } 
        if (success) {
            cout << prob << '\n';
        } else {
            cout << 0.0 << '\n';
        }
    }
}   