#include <iostream>
#include <stdio.h>

using namespace std;

int main() {
    int P;
    cin >> P;
    int n, p, q;
    for (int i = 0; i < P; ++i) {
        cin >> n;
        scanf("%d/%d", &p, &q);
        if (q == 1) {
            cout << n << " 1/" << p+1 << endl;
            continue;
        }
        int depth = 0;
        while (p > q) {
            p -= q;
            ++depth;
        }
        q -= p;
        p += q;
        for (int j = 0; j < depth; ++j) {
            q += p;
        }
        cout << n << " " << p << "/" << q << endl;
    }
}