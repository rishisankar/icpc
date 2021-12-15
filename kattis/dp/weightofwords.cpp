#include <iostream>
#include <cstring>
using namespace std;

int main() {
    int l, w;
    cin >> l >> w;

    char dp[45][1030][45] = {0};

    for (int i = 0; i < 26; ++i) {
        dp[1][i+1][0] = 'a' + i;
    }

    for (int i = 1; i < l; ++i) {
        for (int j = 0; j < 1001; ++j) {
            if (dp[i][j][0] != 0) {
                for (int k = 0; k < 26; ++k) {
                    if (dp[i+1][j+k+1][0] == 0) {
                        strcpy(&(dp[i+1][j+k+1][0]), &(dp[i][j][0]));
                        dp[i+1][j+k+1][i] = 'a' + k;
                    }
                }
            }
        }
    }

    if (dp[l][w][0] == 0) {
        cout << "impossible\n";
    } else {
        cout << dp[l][w] << '\n';
    }
    
}