#include <bits/stdc++.h>
using namespace std;

// returns length of longest increasing subsequence (given list of DISTINCT integers)

int lis(vector<int>& sequence) {
    if (sequence.empty()) return 0;

    vector<int> table;
    table.push_back(sequence[0]);

    for (int i = 1; i < sequence.size(); ++i) {
        int goal = sequence[i];
        if (goal > table[table.size() - 1]) {
            table.push_back(goal);
        } else {
            *lower_bound(table.begin(), table.end(), goal) = goal;
        }
    }

    return table.size();
}

int main() {
    int p;
    cin >> p;

    vector<int> seq(p);

    for (int i = 0; i < p; ++i) {
        cin >> seq[i];
    }

    cout << lis(seq) << '\n';
}