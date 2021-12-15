#include <iostream>

using namespace std;

int main() {
    bool arr[1001][1001] = {}; //instr (0-999) x playable notes (1-1000)
    int n, m;  
    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        for (int j = 0; j < num; ++j) {
            int tmp;
            cin >> tmp;
            arr[i][tmp] = 1;
        }
    }
    int i = 1; //fix
    int note;
    cin >> note;
    int changesReq = 0;
    if (m == 1) {
        cout << 0 << endl;
        return 0;
    }
    while (true) {
        bool notesInSequence[1001] = {};
        notesInSequence[note] = 1;
        int possible[1001];
        int numP = 0;
        for (int j = 0; j < n; ++j) {
            if (arr[j][note] == 1) {
                possible[numP] = j;
                numP++;
            }
        }
        while (true) {
            if (i == m) {
                cout << changesReq << endl;
                return 0;
            }
            cin >> note;
            i++;
            if (notesInSequence[note] == 1) continue;
            for (int j = 0; j < numP; ++j) {
                if (arr[possible[j]][note] == 0) {
                    possible[j] = possible[numP - 1];
                    numP--;
                    j--;
                }
            }
            if (numP == 0) {
                changesReq++;
                break;
            }
            notesInSequence[note] = 1;
        }
    }
}