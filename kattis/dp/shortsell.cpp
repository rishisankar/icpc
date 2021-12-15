#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {

    ll N, K;
    cin >> N >> K;

    ll maxprofit = 0;
    ll curprofit;
    cin >> curprofit;
    curprofit = curprofit * 100 - K;

    for (int i = 1; i < N; ++i) {
        ll tmp; 
        cin >> tmp;
        tmp *= 100;
        curprofit = max(curprofit - K, tmp - K);
        maxprofit = max(maxprofit, curprofit - tmp);
    }

    maxprofit = max(maxprofit, 0LL);

    cout << maxprofit << '\n';

}