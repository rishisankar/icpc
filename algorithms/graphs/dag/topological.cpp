/* give topological order in O(V+E) (kactl) */
vi topoSort(const vector<vi>& gr) {
	vi indeg(sz(gr)), ret;
	for (auto& li : gr) for (int x : li) indeg[x]++;
	queue<int> q; // use priority_queue for lexic. largest ans.
	rep(i,0,sz(gr)) if (indeg[i] == 0) q.push(i);
	while (!q.empty()) {
		int i = q.front(); // top() for priority queue
		ret.push_back(i);
		q.pop();
		for (int x : gr[i])
			if (--indeg[x] == 0) q.push(x);
	}
	return ret;
}

/* unroll edges in topological order O(n+m) */
vector<pii> topoEdgeList(vector<vi>& adj) {
	vi ts = topoSort(adj);
	vector<pii> edges;
	for (int i : ts) {
		for (int x : adj[i]) {
			edges.push_back({i,x});
		}
	}
	return edges;
}