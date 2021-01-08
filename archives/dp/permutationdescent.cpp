#include <bits/stdc++.h>
using namespace std;

vector<vector<long long>> memo(101, vector<long long>(101, -1));

long long pdc(int N, int v) {
    if (v >= N) return 0;
    if (v == 0) return 1;
    if (v < 0) return 0;
    if (memo[N][v] != -1) {
        return memo[N][v];
    } else {
        return memo[N][v] = (pdc(N-1,v) * (v+1) + pdc(N-1,v-1) * (N-v)) % 1001113;
    }
}

int main() {
    int P;
    cin >> P;
    for (int i = 0; i < P; ++i) {
        int K, N, v;
        cin >> K >> N >> v;
        cout << K << ' ' << pdc(N, v) << '\n';
    }
}