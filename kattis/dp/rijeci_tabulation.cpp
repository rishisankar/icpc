#include <iostream>
using namespace std;

int main() {
    int K;
    cin >> K;

    int table[46];
    table[0] = 0;
    table[1] = 1;

    for (int i = 2; i <= K; ++i) {
        table[i] = table[i-1] + table[i-2];
    }

    cout << table[K-1] << " " << table[K] << endl;
}

