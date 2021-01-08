#include <iostream>
using namespace std;

int main() {
    int l, n, m;
    cin >> l >> n >> m;
    if (l == 8) {
        if (n >= 2 && m >= 2) {
            cout << 2 << endl;
            cout << "1 2 1 2 1 2 1 2" << endl;
            cout << "2 1 2 1 2 1 2 1" << endl;
        } else {
            cout << -1 << endl;
        }
    } else {
        if (n >= 3 && m >= 3) {
            cout << 3 << endl;
            cout << "1 2 3 1 2 3 1 2 3" << endl;
            cout << "2 3 1 2 3 1 2 3 1" << endl;
        } else {
            cout << -1 << endl;
        }
    }
}