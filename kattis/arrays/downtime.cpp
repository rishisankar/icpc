#include <bits/stdc++.h>
using namespace std;

int main() {

    int n, k;
    cin >> n >> k;

    int arr[101002] = {0};

    int servers = 0;

    for (int i = 0; i < n; ++i) {
        int tmp;
        cin >> tmp;
        for (int j = tmp; j < tmp + 1000; ++j) {
            arr[j] += 1;
            servers = max(servers, arr[j]);
        }
    }

    cout << (servers+k-1)/k << endl;
}