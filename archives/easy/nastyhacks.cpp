#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    for (int t = 0; t < n; ++t) {
        int a,b,c; cin >> a >> b >> c;
        if (a > b-c) {
            cout << "do not advertise\n";
        } else if (a == b - c) {
            cout << "does not matter\n";
        } else {
            cout << "advertise\n";
        }
    }
}