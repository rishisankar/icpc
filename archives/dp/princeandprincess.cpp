#include <bits/stdc++.h>
using namespace std;

int lis(vector<int>& sequence) {
    vector<int> table;
    table.push_back(sequence[0]);
    for (int i = 1; i < sequence.size(); ++i) {
        int goal = sequence[i];
        if (goal > table[table.size() - 1]) {
            table.push_back(goal);
        } else {
            // binary search, want index of first larger elt of table
            int lo = 0, hi = table.size() - 1;
            int mid = 0;
            while (lo <= hi) {
                mid = (lo + hi) / 2;
                if (table[mid] < goal && goal <= table[mid + 1]) {
                    break;
                } else if (table[mid] < goal) {
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }
            table[mid+1] = goal;
        }
    }
    return table.size();
}

int main() {

    int t;
    cin >> t;

    for (int testcase = 0; testcase < t; ++testcase) {

        printf("Case %d: ", testcase+1);

        int n, p, q;
        cin >> n >> p >> q;

        vector<int> value(n*n+1, -1);
        for (int i = 0; i < p+1; ++i) {
            int tmp;
            cin >> tmp;
            value[tmp] = i;
        }

        vector<int> sequence;
        for (int i = 0; i < q+1; ++i) {
            int tmp;
            cin >> tmp;
            // skip princess #s that aren't prince #s
            if (value[tmp] != -1) {
                sequence.push_back(value[tmp]);
            }
        }

        if (sequence.size() == 0) {
            cout << "0\n";
            continue;
        }

        cout << lis(sequence) << '\n';

    }

}