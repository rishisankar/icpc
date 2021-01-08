#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {

    int k;
    cin >> k;

    vector<ll> nums(k);
    vector<char> ops(k);

    vector<vector<ll>> mindp(k, vector<ll>(k, LLONG_MAX));
    vector<vector<ll>> maxdp(k, vector<ll>(k, LLONG_MIN));

    for (int i = 0; i < k; ++i) {
        cin >> nums[i] >> ops[i];
        mindp[i][i] = nums[i];
        maxdp[i][i] = nums[i];
    }

    for (int i = 1; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            int m = j;
            int n = (j+i)%k;
            for (int o = 0; o < i; ++o) {
                int o1 = (j+o)%k;
                int o2 = (j+o+1)%k;
                ll maxa = maxdp[j][o1];
                ll mina = mindp[j][o1];
                ll maxb = maxdp[o2][n];
                ll minb = mindp[o2][n];

                char op = ops[o1];

                ll maxp, minp, maxm, minm, maxt, mint;

                maxp = maxa + maxb;
                minp = mina + minb;

                maxm = maxa - minb;
                minm = mina - maxb;

                maxt = max(max(maxa * maxb, maxa * minb), max(mina * maxb, mina * minb));
                mint = min(min(maxa * maxb, maxa * minb), min(mina * maxb, mina * minb));

                if (op == '+') {
                    maxdp[m][n] = max(maxdp[m][n],maxp);
                    mindp[m][n] = min(mindp[m][n],minp);
                } else if (op == '-') {
                    maxdp[m][n] = max(maxdp[m][n],maxm);
                    mindp[m][n] = min(mindp[m][n],minm);
                } else if (op == '*') {
                    maxdp[m][n] = max(maxdp[m][n],maxt);
                    mindp[m][n] = min(mindp[m][n],mint);
                } else if (op == '?') {
                    maxdp[m][n] = max(maxdp[m][n], max(max(maxp, maxm), maxt));
                    mindp[m][n] = min(mindp[m][n], min(min(minp, minm), mint));
                }
            }

        }
    }

    for (int i = 0; i < k; ++i) {
        int j = (i + k - 1)%k;
        cout << abs(mindp[i][j]) << abs(maxdp[i][j]);
    }
    cout << '\n';

}