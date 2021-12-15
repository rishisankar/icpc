#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> papers(n);

    for (int i = 0; i < n; ++i) {
        cin >> papers[i];
    }

    sort(papers.begin(), papers.end());

    /* this works!
    for (int i = n; i > 0; --i) {
        if (papers[n-i] >= i) {
            cout << i << '\n';
            return 0;
        }
    }
    cout << 0 << '\n';
    */

    int l = 0, r = n-1;
    while (l <= r) {
        int mid = (l+r)/2;
        if (papers[mid] >= (n-mid)) {
            if (l == r) {
                cout << n-mid << '\n';
                return 0;
            }
            r = mid;
        }
        else l = mid + 1;
    }
    cout << 0 << '\n';
}