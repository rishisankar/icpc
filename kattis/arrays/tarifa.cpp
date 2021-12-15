#include <bits/stdc++.h>
using namespace std;

int main() {

    int X;
    cin >> X;
    int count = X;
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        int tmp; cin >> tmp;
        count += X - tmp;
    }
    cout << count << '\n';

}