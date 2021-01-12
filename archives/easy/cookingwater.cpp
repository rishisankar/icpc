#include <bits/stdc++.h>
using namespace std;

int main() {
    int N; cin >> N;

    int lower, upper;
    cin >> lower >> upper;

    for (int i = 1; i < N; ++i) {
        int tmpl, tmpr;
        cin >> tmpl >> tmpr;
        lower = max(lower, tmpl);
        upper = min(upper, tmpr);
    }
    if (lower > upper) {
        cout << "edward is right\n";
    } else {
        cout << "gunilla has a point\n";
    }
}