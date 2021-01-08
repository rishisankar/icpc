// doesn't work!

#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ll;
const ll INF = ULLONG_MAX;

// use for adjacency list
struct flow {
    ll start, end, capacity;
    flow* opposite;
    flow() {}
    flow(ll _start, ll _end, ll _capacity) : start(_start), end(_end), capacity(_capacity) {}
};

ll maxflow_bfs(ll source, ll sink, vector<vector<flow*>>& flowchart, vector<flow*>& parent) {
    fill(parent.begin(), parent.end(), nullptr);
    queue<pair<flow*,int>> q;
    flow temp(-1, source, INF);
    q.push({&temp, INF});
    parent[source] = &temp;

    while (!q.empty()) {
        flow* prev = q.front().first;
        ll tmpflow = q.front().second;
        q.pop();
        for (flow* f : flowchart[prev->end]) {
            if (parent[f->end] == nullptr && f->capacity > 0) {
                parent[f->end] = f;
                ll new_flow = min(tmpflow, f->capacity);
                if (f->end == sink) return new_flow;
                q.push({f, new_flow});
            }
        }
    }

    return 0;
}

ll maxflow(ll source, ll sink, vector<vector<flow*>>& flowchart, int n) {
    ll count = 0;
    vector<flow*> parent(n); // for bfs trace
    ll new_flow;
    while (new_flow = maxflow_bfs(source, sink, flowchart, parent)) {
        count += new_flow;
        flow* cur = parent[sink];
        while (true) {
            cur->capacity -= new_flow;
            cur->opposite->capacity += new_flow;
            if (cur->start == source) break;
            cur = parent[cur->start];
        }
    }
    return count;
}

int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<flow*>> flowchart(2*N+2);
    for (int i = 0; i < M; ++i) {
        ll start, finish;
        cin >> start >> finish;
        finish += N;
        flow* tmp = new flow(start, finish, 1);
        flow* opp = new flow(finish, start, 0);
        tmp->opposite = opp;
        opp->opposite = tmp;
        flowchart[start].push_back(tmp);
        flowchart[finish].push_back(opp);
    }
    for (int i = 0; i < N; ++i) {
        flow* tmp = new flow(2*N, i, 1);
        flow* opp = new flow(i, 2*N, 0);
        flow* tmp2 = new flow(2*N+1, N+i, 0);
        flow* opp2 = new flow(N+i, 2*N+1, 1);
        tmp->opposite = opp;
        opp->opposite = tmp;
        tmp2->opposite = opp2;
        opp2->opposite = tmp2;
        flowchart[2*N].push_back(tmp);
        flowchart[i].push_back(opp);
        flowchart[2*N+1].push_back(tmp2);
        flowchart[N+i].push_back(opp2);
    }

    ll count = maxflow(2*N, 2*N+1, flowchart, 2*N+2);

    if (count == N) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }


}