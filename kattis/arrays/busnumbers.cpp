#include <bits/stdc++.h>
using namespace std;

int main() {

    int N;
    cin >> N;
    vector<int> arr(N+3, -1);
    for (int i = 0; i < N; ++i) {
        cin >> arr[i];
    }


    sort(arr.begin(), arr.begin() + N);

    bool first = true;
    for (int i = 0; i < N; ++i) {
        if (!first) cout << ' ';
        else first = false;

        cout << arr[i];

        if (arr[i+2] == arr[i]+2) {
            cout << '-';
            for (i += 2; arr[i+1] == arr[i]+1; ++i);
            cout << arr[i];
        }
    }
    cout << endl;

}