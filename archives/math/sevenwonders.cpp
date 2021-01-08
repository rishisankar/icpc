#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;

    long long t = 0, c = 0, g = 0;

    for (int i = 0; i < s.size(); ++i) {
        if (s.at(i) == 'T') ++t;
        else if (s.at(i) == 'C') ++c;
        else ++g;
    }

    long long res = t * t + g * g + c * c + 7 * min(t,min(c,g));

    cout << res << '\n';
}