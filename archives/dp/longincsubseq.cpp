#include <bits/stdc++.h>
using namespace std;

void lis(vector<int>& sequence) {
    if (sequence.empty()) {
        cout << "0\n\n";
    }

    vector<int> parent(sequence.size(), -1);

    vector<int> table;
    vector<int> indexTable;
    table.push_back(sequence[0]);
    indexTable.push_back(0);

    for (int i = 1; i < sequence.size(); ++i) {
        int goal = sequence[i];
        if (goal > table[table.size() - 1]) {
            table.push_back(goal);
            indexTable.push_back(i);
            parent[i] = indexTable[table.size() - 2];
        } else {
            auto it = lower_bound(table.begin(), table.end(), goal);
            *it = goal;
            int index = it - table.begin();
            indexTable[index] = i;
            parent[i] = index >= 1 ? indexTable[index - 1] : -1;
        }
    }

    cout << table.size() << '\n';
    
    vector<int> backtrace(table.size());
    backtrace[table.size() - 1] = indexTable[table.size() - 1];
    for (int i = table.size() - 2; i >= 0; --i) {
        backtrace[i] = parent[backtrace[i+1]];
    }
    for (int i : backtrace) {
        cout << i << ' ';
    }
    cout << '\n';
}

int main() {
    int n;
    while (cin >> n) {
        vector<int> seq(n);
        for (int i = 0; i < n; ++i) {
            cin >> seq[i];
        }
        lis(seq);
    }
}