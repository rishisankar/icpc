// can use similar implementation for general bit trie problems!

/*
Returns the max XOR value of any pair of numbers in the array
B = max # of bits in value
time: O(n*B)

can be used for max xor subarray too
tested on cses/additional/maximum_xor_subarray
*/
struct bt {
    int p0 = -1;
    int p1 = -1;
};
ull max_xor_pair(vector<ull>& v, int B) {
    int n = sz(v), nxt = 1;
    vector<bt> trie(B*n+1);
    ull bst = 0;
    rep(i,0,n) {
        if (i>0) {
            // check stuff currently in trie
            int cur = 0;
            ull nv = 0;
            rep(j,0,B) {
                nv<<=1;
                bool g1 = false;
                if (((v[i] >> (B-1-j))&1)) {
                    // val is a 1
                    if (trie[cur].p0 == -1) g1 = true;
                } else {
                    // val is a 0
                    if (trie[cur].p1 != -1) g1 = true;
                }
                if (g1) {
                    nv++;
                    cur = trie[cur].p1;
                } else cur = trie[cur].p0;
            }
            bst = max(bst,nv^v[i]);
        }
        // insert into trie
        int cur = 0;
        rep(j,0,B) {
            int& ptr = ((v[i] >> (B-1-j))&1) ? trie[cur].p1 : trie[cur].p0;
            if (ptr == -1) ptr = nxt++;
            cur = ptr;
        }
    }
    return bst;
}