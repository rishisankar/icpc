#include <bits/stdc++.h>
using namespace std;

int main() {

    int N; cin >> N;
    for (int i = 0; i < N; ++i) {
        int K; cin >> K;
        int sum = 1-K;
        for (int j = 0; j < K; ++j) {
            int tmp; cin >> tmp;
            sum += tmp;
        }
        cout << sum << '\n';
    }

}