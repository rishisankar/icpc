#include <bits/stdc++.h>
using namespace std;

int main() {

    int k; cin >> k;
    string s1,s2;
    cin >> s1 >> s2;

    int same = 0;
    int different = 0;

    for (int i = 0; i < s1.size(); ++i) {
        if (s1.at(i) == s2.at(i)) {
            ++same;
        } else {
            ++different;
        }
    }

    if (same >= k) {
        cout << k + different << '\n';
    } else {
        cout << same + different - (k - same) << '\n';
    }

}