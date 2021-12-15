#include <bits/stdc++.h>

#define PI 3.1415926535897932384626433832795

using namespace std;

// codeforces

int main() {

    cout.setf(ios::fixed);
    cout.precision(10);

    int T;
    int n;

    cin >> T;

    for (int testcases = 0; testcases < T; ++testcases) {

        int n;
        cin >> n;
        
        long double ans = 1.0 / tan(PI / n / 2.0);

        cout << ans << '\n';

    }

}