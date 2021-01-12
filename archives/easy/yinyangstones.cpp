#include <bits/stdc++.h>
using namespace std;

int main() {
    string s; cin >> s;
    int w = 0; int b = 0;
    for (int i = 0; i < s.size(); ++i) {
        char c = s.at(i);
        if (c == 'W') ++w; else ++b;
    }
    if (w == b) cout << "1\n"; else cout << "0\n";
}