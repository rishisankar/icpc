#include <iostream>
#include <string>
#include <math.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    if (n == 0) {
        cout << 0 << endl;
        return 0;
    }
    if (n == 1) {
        cout << 1 << endl;
        return 0;
    }
    int minIndex = 20;
    int count = 0;
    while (n != 0) {
        while (pow(2, minIndex) > n) {
            minIndex--;
        }
        n -= pow(2, minIndex);
        ++count;
    }
    cout << count << endl;

}