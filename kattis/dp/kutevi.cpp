#include <iostream>

using namespace std;

int main() {
    int possible[361] = {};

    int K, N;
    cin >> N >> K;

    for (int i = 0; i < N; ++i) {
        int num;
        cin >> num;
        int tmp = 0;
        while (true) {
            tmp = (tmp + num) % 360;
            if (possible[tmp] == num) break;
            possible[tmp] = num;
        }
    }

    for (int i = 0; i < K; ++i) {
        int num;
        cin >> num;
        if (possible[num] > 0) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}