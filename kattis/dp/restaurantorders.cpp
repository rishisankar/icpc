#include <iostream>
#include <stack>

using namespace std;

int main() {

    int N, M;
    cin >> N;
    int prices[101];
    int dp[30001] = {0};

    int priceLookup[1001];
    for (int i = 0; i < N; ++i) {
        cin >> prices[i];
        priceLookup[prices[i]] = i + 1;
    }
    cin >> M;
    int orders[1001];
    int maxOrder = 0;
    for (int i = 0; i < M; ++i) {
        cin >> orders[i];
        if (orders[i] > maxOrder) maxOrder = orders[i];
    }

    for (int i = 0; i < N; ++i) {
        int price = prices[i];
        if (dp[price])
            dp[price] = -1;
        else
            dp[price] = -2;
        //can be sped up using vector..
        for (int i = 0; i <= maxOrder - price; ++i) {
            if (dp[i]) {
                if (dp[i + price]) {
                    dp[i + price] = -1;
                } else {
                    dp[i + price] = i;
                }
            }
        }

    }

    /*for (int i = 0; i < 15; ++i) {
        cout << dp[i] << " ";
    }
    cout << endl;*/

    for (int i = 0; i < M; ++i) {
        int cur = orders[i];
        if (dp[cur] == 0) {
            cout << "Impossible" << endl;
            continue;
        }

        stack<int> stk;
        bool amb = false;
        while (dp[cur] != -2) {
            if (dp[cur] == -1) {
                amb = true;
                break;
            }
            stk.push(priceLookup[cur - dp[cur]]);
            cur = dp[cur];
        }
        if (amb) {
            cout << "Ambiguous" << endl;
            continue;
        }
        stk.push(priceLookup[cur]);

        cout << stk.top();
        stk.pop();
        while (!stk.empty()) {
            cout << " " << stk.top();
            stk.pop();
        }
        cout << endl;
    }
}