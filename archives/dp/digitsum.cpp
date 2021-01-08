#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ll;

ll tenpow(int x) {
    ll num = 1;
    for (int i = 0; i < x; ++i) {
        num *= 10;
    }
    return num;
}
 
int countDigits(ll n) {
    int count = 0;
    while (n != 0) {
        n /= 10;
        ++count;
    }
    return count;
}

vector<ll> dp(19);

ll calc(ll num) {

    int sums[] = {0, 1, 3, 6, 10, 15, 21, 28, 36, 45};
    // 0-63513 = (0-59999) + (60000-62999) + (63000-63499) + (63500-63509) + (63510-63513)
    // 0-10: (0-9) + (10 - 10)

    int digits = countDigits(num);

    ll sum = 0;
    ll curdigitsum = 0;

    for (int i = digits - 1; i >= 0; --i) {
        ll digit = (num / tenpow(i)) % 10;
        //printf("NUM: %lld, digits: %d, cur: %d\n", num, digits, digit);

        ll add;
        if (i != 0) {
            ll numcount = digit * tenpow(i);
            ll tmp = digit == 0 ? 0 : sums[digit-1] * tenpow(i);
            add = numcount * curdigitsum + dp[i] * digit + tmp;
        } else {
            add = (digit + 1) * curdigitsum + sums[digit];
        }

        //ll add = sums[digit-1] * tenpow(i) +  + curdigitsum * tenpow(i) * digit;

        curdigitsum += digit;
        sum += add;
    }

    return sum;
}

int main() {

    // dp[1]: digit sum (0-9)
    // dp[2]: digit sum (00-99)
    // dp[3]: digit sum (000-999)
    // ...
    // dp[16]: digit sum etc.

    dp[0] = 0;
    dp[1] = 45;
    for (int i = 2; i <= 18; ++i) {
        dp[i] = dp[1] * tenpow(i-1) + 10 * dp[i-1];
    }

    int t;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        ll num1, num2;
        cin >> num1 >> num2;
        // cout << num1 << " " << num2 << "\n";
        if (num1 == 0) {
            cout << calc(num2) << '\n';
        } else {
            cout << calc(num2) - calc(num1-1) << '\n';
        }
    }
    
}