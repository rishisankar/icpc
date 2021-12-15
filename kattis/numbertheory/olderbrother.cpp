#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n;
    cin >> n;

    if (n == 1) {
        cout << "no\n";
        return 0;
    }

    long long divisor = -1;


    for (long long i = 2; i < 1000000; ++i) {
        if (n % i == 0) {
            divisor = i;
            break;
        }
    }

    if (divisor == -1) {
        cout << "yes" << '\n';
        return 0;
    }

    while (n != 1) {
        if (n % divisor == 0) {
            n /= divisor;
        } else {
            cout << "no\n"; 
            return 0;
        }
    }
    cout << "yes\n";

    
}