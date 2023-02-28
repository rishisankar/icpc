/*
Find closest left neighbor with smaller value for each index
Monotonic stack to find max { j : j<i, v[j] < v[i] }, -1 if none
O(n)
*/
vi closestSmaller(VLL& v) {
  stack<int> s;
  vector<int> prev(n,-1);
  rep(i,0,n) {
      while (!s.empty() && v[s.top()] >= v[i]) s.pop();
      if (!s.empty()) prev[i] = s.top();
      s.push(i);
  }
  return prev;
}
