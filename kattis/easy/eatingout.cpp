#include <bits/stdc++.h>
using namespace std;

int main() {
    int m,a,b,c;
    cin >> m >> a >> b >> c;

    int overlap = a+b-m >= 0 ? a+b-m : 0;
    overlap = m - overlap;
    if (c <= overlap) {
        cout << "possible\n";
    } else {
        cout << "impossible\n";
    }
}