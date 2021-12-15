#include <bits/stdc++.h>
using namespace std;

int main() {

    int N;
    cin >> N;

    int s[1000002] = {0};

    int count = 0;

    for (int i = 0; i < N; ++i) {

        int tmp;
        cin >> tmp;

        int lookup = s[tmp];
        if (lookup == 0) {
            count++;
        } else {
            s[tmp]--;
        }
        if (tmp >= 2) s[tmp-1] += 1;
    }

    cout << count << endl;


}