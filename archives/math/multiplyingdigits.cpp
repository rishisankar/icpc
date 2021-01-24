#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ll b,n;
    cin >> b >> n;

    if (n == 1) {
        cout << "1\n";
        return 0;
    }

    vector<ll> digits;

    while (n != 1) {
        bool found = false;
        for (ll i = b-1; i > 1; --i) {
            if (n % i == 0) {
                digits.push_back(i);
                cout << "pushing back " << i << '\n';
                n/=i;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "impossible\n";
            return 0;
        }
    }

    sort(digits.begin(), digits.end(), greater<int>());

    ll res = 0;
    ll base = 1;

    for (int i = 0; i < digits.size(); ++i) {
        res += base * digits[i];
        base *= b;
    }

    cout << res << '\n';
}