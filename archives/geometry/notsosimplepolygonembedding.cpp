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

        long double sidelen = 0.5 / sin(PI / 2.0 / n);
        
        long double ans = 2 * sidelen * cos(PI / 4.0 / n);

        cout << ans << '\n';

    }

}