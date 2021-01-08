#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main() {
    int tree[101];
    for (int i = 0; i < 101; ++i) {
        tree[i] = -1;
    }
    int K, a, b;
    cin >> K;
    while (true) {
        cin >> a;
        if (a == -1) break;

        string line;
        getline(cin, line);
        stringstream iss(line);
        int prev = -1;
        while (true) {    
            iss >> b;
            if (b == prev) break;
           // cout << b << endl;
            tree[b] = a;
            prev = b;
        }
    }
    cout << K;
    while (true) {
        K = tree[K];
        if (K == -1) break;
        cout << ' ' << K;
    }
    cout << endl;
    
}