#include <bits/stdc++.h>
using namespace std;

int main() {
    int a,b,c,n;
    cin >> a >> b >> c >> n;

    bool possible = true;
    if (n < 3) possible = false;
    if (a+b+c < n) possible = false;
    if (a == 0 || b == 0 || c == 0) possible = false;
    cout << (possible ? "YES\n" : "NO\n");
}