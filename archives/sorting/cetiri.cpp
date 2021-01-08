#include <bits/stdc++.h>
using namespace std;

int main() {

    int a,b,c;
    cin >> a >> b >> c;

    vector<int> asdf;
    asdf.push_back(a);
    asdf.push_back(b);
    asdf.push_back(c);
    sort(asdf.begin(), asdf.end());

    int k1 = asdf[1] - asdf[0];
    int k2 = asdf[2] - asdf[1];
    if (k1 == k2) {
        cout << asdf[2] + k1 << endl;
    } else if (k1 > k2) {
        cout << asdf[0] + k2 << endl;
    } else {
        cout << asdf[1] + k1 << endl;
    }

}