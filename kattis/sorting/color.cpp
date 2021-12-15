#include <bits/stdc++.h>
using namespace std;

int main() {

    int s,c,k;
    cin >> s >> c >> k;

    vector<int> socks(s);
    for (int i = 0; i < s; ++i) {
        cin >> socks[i];
    }

    sort(socks.begin(), socks.end());

    int count = 1;
    int cur = 0;
    for (int i = 1; i < s; ++i) {
        if (i - cur >= c || socks[i] - socks[cur] > k) {
            ++count;
            cur = i;
        }
    }

    cout << count << '\n';

}