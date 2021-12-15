#include <bits/stdc++.h>
using namespace std;

int main() {
    unsigned long long n,m,a,c,x;
    cin >> n >> m >> a >> c >> x;
    a %= m;

    vector<unsigned long long> seq(n);

    for (int i = 0; i < n; ++i) {
        x = ((((x % m) * a) % m) + c) % m;
        seq[i] = x;
    }

    int count = 0;
    for (int i = 0; i < n; ++i) {

        int l = 0, r = n - 1;
        while (l <= r) {

            int mid = (l+r)/2;

            if (seq[mid] == seq[i]) {
                ++count;
                break;
            } else if (seq[mid] > seq[i]) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
    }
    cout << count << '\n';

}