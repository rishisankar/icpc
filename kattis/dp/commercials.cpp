#include <bits/stdc++.h>
using namespace std;

int main() {

    int N, P;
    cin >> N >> P;

    int curprofit;
    cin >> curprofit;
    curprofit -= P;
    int maxprofit = curprofit;

    for (int i = 1; i < N; ++i) {
        int tmp;
        cin >> tmp;
        tmp -= P;
        curprofit = max(curprofit + tmp, tmp);
        maxprofit = max(maxprofit, curprofit);
    }

    cout << maxprofit << '\n';

}