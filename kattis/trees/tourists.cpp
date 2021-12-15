#include <iostream>
#include <vector>

using namespace std;

int depth[200001];
int parent[200001];
vector<int> adjacent[200001];

void dfs(int dep, int num, int prev) {
    depth[num] = dep;
    parent[num] = prev;
    for (int i = 0; i < adjacent[num].size(); ++i) {
        if (adjacent[num][i] == prev) continue;
        dfs(dep+1, adjacent[num][i], num);
    }
}

int LCA(int i1, int i2) {
    if (parent[i1] == -1) 
        return i1;
    if (parent[i2] == -1)
        return i2;
    if (i1 == i2)
        return i1;
    if (depth[i1] >= depth[i2])
        return(LCA(parent[i1], i2));
    else
        return(LCA(i1,parent[i2]));
}

int dist(int i1, int i2) {
    return depth[i1] + depth[i2] - 2*depth[LCA(i1,i2)] + 1;
}

int main() {
    int n;
    cin >> n;

    int a,b;
    for (int i = 0; i < n-1; ++i) {
        cin >> a >> b;
        adjacent[a].push_back(b);
        adjacent[b].push_back(a);
    }
    dfs(0, 1, -1);

    int sum = 0;
    for (int i = 1; i <= n/2; ++i) {
        for (int j = 2*i; j <= n; j += i) {
            sum += dist(i,j);
        }
    }
    
    cout << sum << endl;
}