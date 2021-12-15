#include <bits/stdc++.h>
using namespace std;

int main() {

    int n;
    cin >> n;

    vector<int> arr(n);

    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    vector<int> max_left(n);
    vector<int> min_right(n);

    max_left[0] = arr[0];
    min_right[n-1] = arr[n-1];

    for (int i = 1; i < n; ++i) {
        max_left[i] = max(max_left[i-1], arr[i]);
    }

    for (int i = n-2; i >= 0; --i) {
        min_right[i] = min(min_right[i+1], arr[i]);
    }

    int count = 0;
    for (int i = 1; i < n-1; ++i) {
        if (max_left[i-1] <= arr[i] && min_right[i+1] > arr[i]) ++count;
    }

    if (arr[0] < min_right[1]) ++count;
    if (arr[n-1] >= max_left[n-2]) ++count;

    cout << count << '\n';
}