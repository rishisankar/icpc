struct st {
    int pt;
    long long weight;
    st() {}
    st(int _pt, long long _weight) : pt(_pt), weight(_weight) {}
};

// finds shortest path length to pts 1 ... N from source pt given weighted adjacency list
vector<long long> dijkstra(int source, vector<vector<st>> adj_list, int N) {
    vector<long long> dists(N+1, LLONG_MAX);
    vector<long long> shortest(N+1, -1);
    dists[source] = 0;
    while(true) {
        int minpt = 0;
        for (int i = 1; i <= N; ++i) {
            if (shortest[i] == -1 && dists[i] <= dists[minpt]) {
                minpt = i;
            }
        }
        if (minpt == 0) break;
        shortest[minpt] = dists[minpt];
        for (st edge : adj_list[minpt]) {
            if (shortest[edge.pt] == -1) {
                dists[edge.pt] = min(dists[edge.pt], edge.weight + dists[minpt]);
            }
        }
    }
    return shortest;
}