#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include <map>
#include <sstream>
#include <algorithm>
#include <stdio.h>
#include <math.h>

using namespace std;

#define PI 3.1415926535897932384626433832795

char grid[1000001];
stack<int> todo;

void addToGrid(int i) {
    if (grid[i] == 'X')
        return;
    todo.push(i);
}

int main() {
    int m, n;
    cin >> m >> n;
    int goal = -1;
    for (int i = 0; i < m*n; ++i) {
        cin >> grid[i];
        if (grid[i] == 'C') {
            todo.push(i);
        }
        if (grid[i] == 'R' && goal == -1) {
            goal = i;
        }
    }
    if (goal == n - 1) {
        cout << "no" << endl;
        return 0;
    }

    while (!todo.empty()) {
        int top = todo.top();
        todo.pop();
        if (grid[top] == 'V') {
            continue;
        } else {
            grid[top] = 'V';
        }
        if (top % n > goal) {
            cout << "yes" << endl;
            return 0;
        }
        if (top >= n) {
            addToGrid(top-n);
            addToGrid(top-n+1);
            if (top % n != 0) {
                addToGrid(top-n-1);
            }
        }
        if (top < n*(m-1)) {
            addToGrid(top+n);
            addToGrid(top+n+1);
            if (top % n != 0) {
                addToGrid(top+n-1);
            }
        }
        if (top % n != 0) {
            addToGrid(top-1);
        }
        addToGrid(top + 1);
    }
    cout << "no" << endl;
    

}