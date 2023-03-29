/*
Longest Increasing Subsequence in O(nlogn)
Numbers don't have to be distinct
*/
#include <bits/stdc++.h>
using namespace std;

// Returns {length, indices of LIS}
pair<int,vector<int>> lis2(vector<int>& sequence) {
    vector<int> indices;
    if (sequence.empty()) return {0,indices};

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
    
    indices.resize(table.size());
    indices[table.size() - 1] = indexTable[table.size() - 1];
    for (int i = table.size() - 2; i >= 0; --i) {
        indices[i] = parent[indices[i+1]];
    }
    return {table.size(), indices};
}

// Returns length only (tested on cses/dp/increasing_subsequence)
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

// testing / example usage
int main() {
    // lis: 5 {1,2,3,5,15}
    vector<int> v1{1,5,2,-3,5,6,3,1,5,5,-8,15};
    cout << lis(v1) << '\n';
    int x; vector<int> res;
    tie(x,res) = lis2(v1);
    cout << x << '\n';
    for (int i : res) cout << i << ' '; cout << '\n';
    for (int i : res) cout << v1[i] << ' '; cout << '\n';
}
