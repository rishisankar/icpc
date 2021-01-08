#include <bits/stdc++.h>

using namespace std;

int main() {

    cout.setf(ios::fixed);
    cout.precision(10);

    long double C;
    cin >> C;

    int L;
    cin >> L;

    long double total = 0;
    for (int i = 0; i < L; ++i) {
        long double w,h;
        cin >> w >> h;
        total += C * w * h;
    }

    cout << total << '\n';

}