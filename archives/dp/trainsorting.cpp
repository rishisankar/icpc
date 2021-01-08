#include <bits/stdc++.h>
using namespace std;

int main() {

    int n;
    cin >> n;

    vector<int> trains(n);
    for (int i = 0; i < n; ++i) {
        cin >> trains[i];
    }

    if (n == 0) {
        cout << "0\n";
        return 0;
    }

    // longest increasing/decreasing sequences starting with train n
    vector<int> lis(n);
    vector<int> lds(n);

    lis[n-1] = 1;
    lds[n-1] = 1;

    for (int i = n-2; i >= 0; --i) {
        lis[i] = 1;
        lds[i] = 1;
        for (int j = i + 1; j < n; ++j) {
            if (trains[i] > trains[j]) {
                lds[i] = max(lds[i], lds[j] + 1);
            } else {
                lis[i] = max(lis[i], lis[j] + 1);
            }
        }
    }

    int maximum = 1;

    // iterate through all possible first trains Erin could pick
    for (int i = 0; i < n; ++i) {
        maximum = max(maximum, lis[i] + lds[i] - 1);
    }

    cout << maximum << '\n';

}