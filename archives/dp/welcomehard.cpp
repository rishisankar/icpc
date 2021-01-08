#include <iostream>
#include <string>
using namespace std;

int main() {
    string target = "welcome to code jam";
    int T;
    cin >> T;
    cin.ignore(10000, '\n');
    for (int i = 0; i < T; ++i) {
        string s;
        getline(cin, s);
        int dp[500][19];

        dp[0][0] = s.at(0) == 'w' ? 1 : 0;
        for (int j = 1; j < 19; ++j) {
            dp[0][j] = 0;
        }

        for (int j = 1; j < s.size(); ++j) {
            for (int k = 0; k < 19; ++k) {
                dp[j][k] = dp[j-1][k] % 10000;
            }

            char c = s.at(j);
            if (c == 'w') {
                dp[j][0]++;
            }
            for (int k = 1; k < target.size(); ++k) {
                char ch = target.at(k);
                if (c == ch) {
                    dp[j][k] += dp[j][k-1];
                }
            }
        }
        cout << "Case #" << i+1 << ": ";
        int res = dp[s.size() - 1][18] % 10000;
        if (res < 1000) cout << '0';
        if (res < 100) cout << '0';
        if (res < 10) cout << '0';
        cout << res << endl;
    }
}