#include <bits/stdc++.h>
using namespace std;

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
    string s;
    cin >> s;
    vector<int> sequence(s.size());
    for (int i = 0; i < s.size(); ++i) {
        int tmp = s.at(i) - 'a';
        sequence[i] = tmp;
    }
    cout << 26 - lis(sequence) << '\n';
}