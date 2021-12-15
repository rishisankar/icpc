#include <iostream>

using namespace std;

int opposite(int a) {
    if (a == 0) return 1;
    return 0;
}

int main() {
    int N;
    cin >> N;
    int nodes[100001];
    for (int i = 0; i < 100001; ++i) {
        nodes[i] = -1;
    }
    int a,b;
    for (int i = 0; i < N-1; ++i) {
        cin >> a >> b;
        if (nodes[a] == -1) {
            if (nodes[b] == -1) {
                nodes[a] = 1;
                nodes[b] = 0;
            } else {
                nodes[a] = opposite(nodes[b]);
            }
        } else {
            if (nodes[b] == -1) {
                nodes[b] = opposite(nodes[a]);
            } else {
                if (nodes[a] == nodes[b]) {
                    cout << 0 << endl;
                    continue;
                }
            }
        }
        cout << nodes[a] << endl;
    }
}