#include <bits/stdc++.h>
using namespace std;

// initialize is_prime to true with size n+1
int sieve(int n, vector<bool>& is_prime) {
    int count = n-1;
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                if (is_prime[j]) {
                    is_prime[j] = false;
                    --count;
                }
            }
        }
    }
    return count;
}

int main() {
    int n, q;
    cin >> n >> q;
    vector<bool> is_prime(n+1, true);
    cout << sieve(n,is_prime) << '\n';
    for (int i = 0; i < q; ++i) {
        int tmp; cin >> tmp;
        cout << is_prime[tmp] << '\n';
    }
}