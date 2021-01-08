#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ll;

vector<ll> fib(91);

char batman(ll N, ll K) {

    if (N == 1) {
        return 'N';
    }
    if (N == 2) {
        return 'A';
    }
    if (N > 92) {
        return batman(N-2, K);
    } else if (K > fib[N-2]) {
        return batman(N-1, K-fib[N-2]);
    } else {
        return batman(N-2, K);
    }

}

int main() {

    fib[0] = 0;
    fib[1] = 1;
    for (int i = 2; i < 91; ++i) {
        fib[i] = fib[i-1] + fib[i-2];
    }

    ll N, K;
    cin >> N >> K;

    cout << batman(N,K) << '\n';

}