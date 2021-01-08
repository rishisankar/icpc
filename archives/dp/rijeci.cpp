#include <iostream>
using namespace std;

int memo[46];

int fib(int n) {
    if (n == 0) {
        return 0;
    }

    if (memo[n] != 0) {
        return memo[n];
    }

    return memo[n] = fib(n-1) + fib(n-2);
}

int main() {
    memo[0] = 0;
    memo[1] = 1;

    int N;
    cin >> N;
    cout << fib(N-1) << " " << fib(N) << endl;
}