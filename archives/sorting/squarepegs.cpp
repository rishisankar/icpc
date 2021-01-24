#include <bits/stdc++.h>

using namespace std;

int main() {

    int N, M, K;
    cin >> N >> M >> K;

    vector<double> plots(N);
    for (int i = 0; i < N; ++i) {
        cin >> plots[i];
    }

    vector<double> houses(M+K);
    for (int i = 0; i < M; ++i) {
        cin >> houses[i];
    }
    for (int i = M; i < M+K; ++i) {
        double tmp;
        cin >> tmp;
        tmp = tmp / 2 * sqrt(2);
        houses[i] = tmp;
    }

    sort(plots.begin(), plots.end());
    sort(houses.begin(), houses.end());

    int count = 0;
    int pi = 0;
    for (int i = 0; i < M+K && pi < N; ++i, ++pi) {
        while (pi < N && plots[pi] <= houses[i]) ++pi;
        if (pi < N) ++count;
    }

    cout << count << '\n';


}