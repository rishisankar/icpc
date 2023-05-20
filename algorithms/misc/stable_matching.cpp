/*
Stable matching (Gale Shapley algorithm), n men to m women (n <= m)
Returns vi(n) of which woman each man is matched to
men_prefs[n][m] gives ordered preference list of each man (0 = highest pref)
women_prefs[m][n] gives ordered preference list of each woman
Time: O(nm)
Tested: kattis/jealousyoungsters
*/
vi stable_matching(int n, int m, vector<vi>& men_prefs, vector<vi>& women_prefs) {
    vi mm(n, -1), wm(m, -1); // matches
    vector<vi> score(m, vi(n)); // woman's ranking of each man (lower score better)
    rep(w,0,m) rep(i,0,n) score[w][women_prefs[w][i]] = i;
    stack<int> unmatched_men;
    vi prop(n); // # women proposed by each man
    rep(i,0,n) unmatched_men.push(i);
    while (!unmatched_men.empty()) {
        int man = unmatched_men.top(); unmatched_men.pop();
        while (prop[man] < m) { // try proposing
            int woman = men_prefs[man][prop[man]++];
            if (wm[woman] == -1) {
                // unmatched woman --> match
                mm[man] = woman;
                wm[woman] = man;
                break;
            } else if (score[woman][man] < score[woman][wm[woman]]) {
                // check if this is better match
                mm[wm[woman]] = -1;
                unmatched_men.push(wm[woman]);
                mm[man] = woman;
                wm[woman] = man;
                break;
            }
        }
    }
    return mm;
}