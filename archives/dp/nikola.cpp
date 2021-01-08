#include <iostream>
using namespace std;

int min(int i, int j) {
    return (i == 0 || i > j) ?  j : i;
}

int main() {
    int N;
    cin >> N;
    int costs[1002];
    int sumCosts = 0;
    for (int i = 0; i < N; ++i) {
        cin >> costs[i];
        sumCosts += costs[i];
    }

    if (N == 2) { 
        cout << costs[1] << endl;
        return 0;
    }
        

    int arr1[1002] = {0};
    int arr2[1002] = {0};
    arr1[0] = costs[0] + costs[1];
    arr1[1] = costs[1];

    bool currArr1 = true;

    int level = 2;

    int optimal = (N-3)*costs[0] + sumCosts;

    bool optimalFound = false;

    while (!optimalFound) {
        int *currArr, *otherArr;
        if (currArr1) {
            currArr = arr1;
            otherArr = arr2;
        } else {
            currArr = arr2;
            otherArr = arr1;
        }
        for (int i = 0; i < N; ++i) {
            otherArr[i] = 0;
        }
        optimalFound = true;
        for (int i = 0; i < N; ++i) {
            if (currArr[i] == 0) break;

            int prevVal = currArr[i];
            for (int j = i + level; j >= 0; j -= level) {
                if (j >= N) continue;
                if (prevVal < optimal) optimalFound = false;
                prevVal = otherArr[j] = min(otherArr[j], prevVal + costs[j]);
            }
            if (i+level == N-1) optimal = min(optimal, otherArr[N-1]);
        }
        level++;
        currArr1 = !currArr1;
    }

    cout << optimal << endl;
}