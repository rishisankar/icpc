#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll gcd(ll a, ll b) { 
    if (a == 0) return b; 
    return gcd(b % a, a); 
} 

int main() {

    int n; cin >> n;

    vector<ll> v(n);
    for (int i = 0; i < n; ++i) cin >> v[i];

    unordered_set<ll> total;
    unordered_set<ll> cur[2];

    for (int i = 0; i < n; ++i) {
        int a = i%2;
        int b = (i+1)%2;
        cur[a].clear();

        for (ll x : cur[b]) {
            ll tmp = gcd(x, v[i]);
            cur[a].insert(tmp);
            total.insert(tmp);
        }
        cur[a].insert(v[i]);
        total.insert(v[i]);
    }

    cout << total.size() << '\n';

}