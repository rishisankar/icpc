#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll cost(int n) {
    ll res = 1;
    for (int i = 0; i < n; ++i) {
        res *= 2;
    }
    return res - 1;
}

ll solve(int N, int* s1, int* s2, int* s3, int n1, int n2, int n3) {

    if (N == 1) {
        if (s1[0] == 1) return 1;
        if (s3[0] == 1) return 0;
        return -1;
    }

    if (s1[0] == N) {
        ll tmp = solve(N-1, s1+1, s3, s2, n1-1, n3, n2);
        if (tmp == -1) return -1;
        return tmp + 1LL + cost(N-1);
    } else if (s3[0] == N) {
        return solve(N-1, s2, s1, s3+1, n2, n1, n3-1);
    } else {
        return -1;
    }


}

int main() {

    int n1,n2,n3;
    int s1[60] = {0};
    int s2[60] = {0};
    int s3[60] = {0};
    cin >> n1;
    for (int i = 0; i < n1; ++i) {
        cin >> s1[i];
    }
    cin >> n2;
    for (int i = 0; i < n2; ++i) {
        cin >> s2[i];
    }
    cin >> n3;
    for (int i = 0; i < n3; ++i) {
        cin >> s3[i];
    }

    ll res = solve(n1+n2+n3, s1, s2, s3, n1, n2, n3);
    if (res == -1) {
        cout << "No\n";
    } else {
        cout << res << '\n';
    }

}