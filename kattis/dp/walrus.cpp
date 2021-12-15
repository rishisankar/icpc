#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    bool dp[2001] = {0};

    for (int i = 0; i < n; ++i) {
        int weight;
        cin >> weight;
        for (int j = 2000-weight; j >= 0; --j) {
            if (dp[j]) {
                dp[j+weight] = true;
            }
        }
        dp[weight] = true;
    }

    for (int i = 0; i < 1000; ++i) {
        if (dp[1000 + i]) {
            cout << 1000+i << endl;
            return 0;
        }
        if (dp[1000 - i]) {
            cout << 1000-i << endl;
            return 0;
        }
    }
}