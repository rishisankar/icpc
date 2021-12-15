#include <iostream>
using namespace std;

int main() {
    int P;
    cin >> P;
    for (int i = 0; i < P; ++i) {
        int K, n, m, k;
        cin >> K >> n >> m >> k;
        int dp[30];
        for (int j = 0; j < n; ++j) {
            int count = 0;
            if ((j+1) % k !=  m) ++count;
            for (int l = 0; l < j; ++l) {
                if ((j-l) % k != m) {
                    count += dp[l];
                }
            }
            dp[j] = count;
        }
        cout << K << " " << dp[n-1] << endl;
    }
}