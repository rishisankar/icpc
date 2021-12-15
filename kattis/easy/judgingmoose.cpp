#include <bits/stdc++.h>
using namespace std;

int main() {
    int l,r;
    cin >> l >> r;

    if (l == r && r == 0) {
        cout << "Not a moose\n";
        return 0;
    }

    int m = min(l,r);
    int ma = max(l, r);

    if (m == ma) {
        cout << "Even " << m*2 << '\n';
        return 0;
    }

    cout << "Odd " << ma*2 << '\n';
}