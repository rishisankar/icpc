#include <bits/stdc++.h>
using namespace std;

int main() {
    int n,p;
    cin >> n >> p;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }
    sort(nums.begin(), nums.end());

    int m = nums[0];

    for (int i = 0; i < n; ++i) {
        int dist = p*(i+1);
        m = min(m, nums[i] - dist);
    }
    cout << nums[0] - m << '\n';
}