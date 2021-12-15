#include <bits/stdc++.h>
using namespace std;

int main() {

    vector<int> tests(4712, INT_MAX);
    tests[1] = 0;

    for (int n = 2; n <= 4711; n++)
        for (int k = 1; k < n; k++)
            tests[n] = min(tests[n], max(k, 1 + tests[n-k]));


    while (true) {
        int n; cin >> n;
        if (n == 0) break;
        cout << tests[n] << '\n';
    }
        
}