#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ll zero = 0;
    ll one = 0;
    ll two = 0;
    ll three = 0;

    ll oldOne, oldTwo, oldThree;

    ll MOD = 1000000007;

    int N; cin >> N;
    string input; cin >> input;
    for (int i = 0; i < N; ++i) {
        int c = input.at(i) - '0';
        if (c == 0) {
            ++zero;
            continue;
        }
        
        oldOne = one;
        oldTwo = two;
        oldThree = three;
        if (c % 3 == 0) {
            one += oldOne;
            two += oldTwo;
            three += oldThree;
            three += 1;
        } else if (c % 3 == 1) {
            one += oldThree;
            two += oldOne;
            three += oldTwo;
            one += 1;
        } else if (c % 3 == 2) {
            one += oldTwo;
            two += oldThree;
            three += oldOne;
            two += 1;
        }
        one %= MOD;
        two %= MOD;
        three %= MOD;
    }

    ll scale = 1;
    for (int i = 0; i < zero; ++i) {
        scale *= 2;
        scale %= MOD;
    }

    ll res = (three * scale) % MOD;

    cout << res << '\n';

}