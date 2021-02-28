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

bool visited[100001] = {false};
vector<int> adj[100001];

void traverse(int i) {
    if (visited[i]) {
        return;
    } else {
        visited[i] = true;
        for (int j = 0; j < adj[i].size(); ++j) {
            traverse(adj[i][j]);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a1, a2;
        cin >> a1 >> a2;
        adj[a1].push_back(a2);
        adj[a2].push_back(a1);
    }
    int start = 1;
    int count = 0;
    while (start <= n) {
        if (visited[start])
            start++;
        else {
            traverse(start);
            count++;
        }
    }
    cout << count << endl;
} 