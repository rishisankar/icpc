#include <bits/stdc++.h>
using namespace std;

struct node {
    unordered_map<int, int> children;
    int minGain;
};

node arr[200005];

void traverse(int i) {
    if (arr[i].children.size() == 0) {
        arr[i].minGain = 0;
        return;
    }
    int minGain = INT_MAX;
    for (auto it = arr[i].children.begin(); it != arr[i].children.end(); it++) {
        traverse(it->first);
        minGain = min(min(minGain, it->second + arr[it->first].minGain), it->second);
    }
    arr[i].minGain = minGain;
}

int main() {
    int n, q;
    cin >> n  >> q;
    for (size_t i = 0; i < n; i++) {
        arr[i] = node();
        arr[i].children = unordered_map<int, int>();
    }
    for (size_t i = 0; i < n-1; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        arr[min(a,b)].children[max(a,b)] = c;
    }
    traverse(1);
    for (size_t i = 0; i < q; i++) {
        int query;
        cin >> query;
        cout << arr[query].minGain << endl;
    }
    return 0;
}