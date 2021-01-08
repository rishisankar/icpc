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

int main() {
    int n, m;
    cin >> n >> m;
    const int maxBound = 100000;
    int dist[maxBound];
    bool visited[maxBound] = {false};
    visited[n] = true;
    dist[n] = 0;
    queue<int> q;
    q.push(n);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        int a, b, c;
        a = x-1;
        b = x+1;
        c = x*2;
        int d = dist[x] + 1;
        if (a == m || b == m || c ==m) {
            cout << d << endl;
            return 0;
        }
        if (a >= 0 && !visited[a]) {
            visited[a] = true;
            q.push(a);
            dist[a] = d;
        } 
        if (b < maxBound - 1 && !visited[b]) {
            visited[b] = true;
            q.push(b);
            dist[b] = d;
        }
        if (c < maxBound - 1 && !visited[c]) {
            visited[c] = true;
            q.push(c);
            dist[c] = d;
        }

    }
}