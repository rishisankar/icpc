// returns length of longest increasing subsequence (given list of ~not necessarily distinct~ integers)

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



// ############### LIS with recovering indices of sequence ####
// prints instead of returning

void lis2(vector<int>& sequence) {
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