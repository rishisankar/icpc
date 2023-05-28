#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a,x) for (auto& a: x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define F first
#define S second
#define pb push_back
#define mp make_pair
typedef long double ld;
#define double ld
typedef __int128_t ll;
#define int ll
typedef pair<int, int> pii;
typedef vector<int> vi;

    unordered_map<string,int> vm;
    vector<string> vmr;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) {
	return os << '(' << p.first << ", " << p.second << ')';
}
template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) {
	os << '{';
	string sep;
	for (const auto &x: v) os << sep << x, sep = ", ";
	return os << '}';
}

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) {
	cerr << ' ' << H; dbg_out(T...);
}

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif
const int MOD = 1e9+7;


  vector<vector<double>> A;
  vector<double> b;
  vector<vector<ll>> AA;
  vector<ll> bb;


bool check(vector<ll> &x)
{
  for (ll l : x) {
    if (l > INT_MAX || l < INT_MIN) return false;
  }
  int m=sz(AA);
  int n=sz(AA[0]);
  vector<ll> res(m,0);
  rep(i,0,m)
  {
    rep(j,0,n)
    res[i]+=AA[i][j]*x[j];
  }
  bool ok=true;
  rep(i,0,m) ok=ok&&(res[i]<=bb[i]);
  return ok;
}

void dfs(int idx, vector<double> &x, vector<ll> &v, vector<vector<ll>> &sol)
{
  int n=sz(x);
  if(idx==n)
  {
    if(check(v))
    sol.pb(v);
    return;
  }

  ll val=(ll)x[idx];
  rep(i,0,20)
  {
    ll offset=i-10;
    v.pb(val-offset);
    dfs(idx+1,x,v,sol);
    if(sz(sol)!=0) return;
    v.pop_back();
  }
}


void vector_print(vector<double> x){

    // print out vector
    if (x.size() != vmr.size()) {
      cout << "No solution\n";
      exit(0);
    }

    // now try a bucnh og values
    vector<ll> v;
    vector<vector<ll>> sol;
    dfs(0,x,v,sol);

    if(sz(sol)==0)
    {
      cout << "No solution\n";
      exit(0);
    }
    

    for (int i = 0; i<x.size(); i++){
        cout << vmr[i] << " := " << (long long)sol[0][i] << "\n";
    }
    exit(0);
}
double get_min(vector<double> v  ){
    // returns minimum value of a vector
    double min = v[0];
    for (int i=0; i<v.size(); i++){
        if (v[i]<min) min = v[i];
    }
    return min;
}
double get_max(vector<double> v  ){
    // returns maximum value of a vector
    double max = v[0];
    for (int i=0; i<v.size(); i++){
        if (v[i]>max) max = v[i];
    }
    return max;
}
/*
-------------------------------------------------------------------
        Fourier Motzkin
-------------------------------------------------------------------
*/
vector<vector<int>> construct_p(set<int, greater<int> > Z, set<int, greater<int> > N, set<int, greater<int> > P){
        // returns an enumeration of Z \cup (N \times P)
        int r = Z.size() + ( N.size() * P.size());
        vector<vector<int>> p(r, vector<int>(2));

        int i = 0;

        // set p = Z \cup (N x P)
        for (set<int, greater<int> >::iterator itr_z = Z.begin(); itr_z != Z.end(); itr_z++)
        {   // add Z
            p[i][0] = *itr_z ;
            p[i][1] = -1; // if an element is in Z, set the second coordinate -1
            i++;
        }
        for (set<int, greater<int> >::iterator itr_n = N.begin(); itr_n != N.end(); itr_n++)
        {
            for (set<int, greater<int> >::iterator itr_p = P.begin(); itr_p != P.end(); itr_p++){
                // add N times P
                p[i][0] = *itr_n ;
                p[i][1] = *itr_p;
                i++;
            }
        }
        return p;
        
    }


Matrix_Vector_Set Fourier_motzkin(std::vector<std::vector<double>> A, std::vector<double> b, int j){
    // Eliminate the j-th variable of Ax <= b
    int n = A[0].size();

    set<int, greater<int> > Z; // zero indices
    set<int, greater<int> > N; // negative indices
    set<int, greater<int> > P; // positive indices
    
    for (int i =0; i< A.size(); i++  )
    {
        if (A[i][j] > 0) {
            P.insert(i); 
        }
        if (A[i][j] < 0) {
            N.insert(i);
        }
        if (A[i][j] == 0) {
            Z.insert(i);
        }
    }
    vector<vector<int>> p = construct_p(Z, N, P);
    int r = p.size();
    vector<double> d(r);
    vector<vector<double>> D(r, vector<double>(n  ));

    for (int i=0; i<r; i++){
        if (p[i][1]== -1){ // if p[i] in Z
            // D_i. <-A_p(i).
            for(int k=0; k<n; k++){
                D[i][k] = A[p[i][0]][k];
            }
            d[i] = b[p[i][0]];

        } else{ // if p(i) in N x P
            int s = p[i][0];
            int t = p[i][1];
            // D_i <- a_tj * A_s - a_sj * A_t
            for(int k=0; k<n; k++){
                D[i][k] = A[t][j] * A[s][k] - A[s][j] * A[t][k];
            }
            d[i] = A[t][j] * b[s] - A[s][j] * b[t];
        }
    }
    Matrix_Vector_Set output; // we cannot return 2 outputs in C++, so use the struct
    output.Matrix = D;
    output.Vector = d;
    output.Set = P;
    return output;
}

/*
-------------------------------------------------------------------
        Get feasable vector
-------------------------------------------------------------------
*/

bool is_valid(vector<double> d){
    // by Fourier-Motzkin there exists a solution, if in the last iteration, all values of the rhs are positive
    for(int i=0; i<d.size(); i++){
        if ( d[i] < 0) return false;
    }
    return true;
}


void calculate_feasable_vector(vector<Matrix_Vector_Set> V){
    vector<double> x(V[0].Matrix[0].size(), 0.0);
    for(int i = V.size()-1; i>= 0; i--){
        if(V[i].Set.size()>0){
            // If U is not empty we choose the minimum over these positiv inequalitys
            vector<double> b_i_a_ix(V[i].Set.size());
            int k = 0;

            for (set<int, greater<int> >::iterator itr = V[i].Set.begin(); itr != V[i].Set.end(); itr++){
                                if (abs(V[i].Matrix[*itr][i]) <= 1e-6) {
                    V[i].Matrix[*itr][i] = 1e-3;
                  }
                b_i_a_ix[k] = ( 1.0/V[i].Matrix[*itr][i] ) *  (V[i].Vector[*itr] - dot_product(get_row(V[i].Matrix, *itr), x));
                k++;
            }
            
            x[i] = get_min(b_i_a_ix);
        } else{// what do we do, if we only have non-positiv a_ik values
            vector<double> b_i_a_ix(V[i].Matrix.size(), INT_MIN);
            for (int k=0; k<V[i].Matrix.size(); k++  ){
                if (V[i].Matrix[k][i] != 0){
                  if (abs(V[i].Matrix[k][i]) <= 1e-6) {
                    V[i].Matrix[k][i] = 1e-3;
                  }
                b_i_a_ix[k] = ( 1.0/V[i].Matrix[k][i] ) *  V[i].Vector[k] - dot_product(get_row(V[i].Matrix, k), x);
                k++;
                }
            }
            x[i] = get_max(b_i_a_ix);
        }   
    }
    vector_print(x);
    return;
}
/*
-------------------------------------------------------------------
        Main function
-------------------------------------------------------------------
*/
int32_t main()
{
  signal(SIGSEGV, [](int32_t) { _Exit(0); });
     /*
    -------------------------------------------------------------------
            Get Input
    -------------------------------------------------------------------
    */

    string t;
    int n;


    while (cin >> t) {
      if (t == "V") {
        string v; cin >> v;
        vm[v] = sz(vm);
        vmr.pb(v);
      } else if (t == "R") {
        n = sz(vm);
        vector<ll> Av;
        rep(i,0,n) {
          long long x; cin >> x;
          Av.pb(x);
        }
        string op; cin >> op;
        if (op == ">=") {
          rep(i,0,n) Av[i]*=-1;
        }
        long long bx; cin >> bx;
        if (op == ">=") bx*=-1;
        bb.pb(bx);
        AA.pb(Av);
      }
    }
    rep(i,0,n) {
      bb.pb(INT_MAX);
      vector<ll> Av;
      rep(j,0,n) {
        if (j == i) Av.pb(1); else Av.pb(0);
      }
      AA.pb(Av);
    }
    rep(i,0,n) {
      bb.pb(-(ll)INT_MIN);
      vector<ll> Av;
      rep(j,0,n) {
        if (j == i) Av.pb(-1); else Av.pb(0);
      }
      AA.pb(Av);
    }

    int m = sz(AA);

    A=vector<vector<double>>(m,vector<double>(n));
    b=vector<double>(m);
    rep(i,0,m) rep(j,0,n) A[i][j]=AA[i][j];
    rep(i,0,m) b[i]=bb[i];

     /*
    -------------------------------------------------------------------
            Process data
    -------------------------------------------------------------------
    */
    // We store everything we need for the ouput vectors in this array
    vector<Matrix_Vector_Set> everything_important(n);

    for(int j=0; j<n; j++ ){
        // Eliminate all Variables and save the produced part-solutions
        Matrix_Vector_Set construct = Fourier_motzkin(A, b, j);
        everything_important[j].Matrix = A;
        everything_important[j].Vector = b;
        everything_important[j].Set = construct.Set;
        A = construct.Matrix;
        b = construct.Vector;
    }

    if (is_valid(b)){
        calculate_feasable_vector(everything_important);
    } else{
        // cout << "empty ";
        A = everything_important[0].Matrix;
        b = everything_important[0].Vector;
        /*
        -------------------------------------------------------------------
                Get the certificate vector
        -------------------------------------------------------------------
        
        We solve
                ( A^T )         ( 0 )
                ( -A^T )  u <=  ( 0 )
                ( -id )         ( 0 )
                ( b^t )         ( -1 )

        Note that this is eqivalent to the one in the Lemma of Farkas.
        We know that if A^Ty=0 then A^t * lambda * y = 0 for every lambda in R, and since y>=0 we know that
        b^Ty < 0   <=>   b^Ty< -1 
        So we can do what we did before on this LP.
        */
        vector<vector<double>> AA(2*n+m+1, vector<double>(m));
        //initialise the new lhs 
            for(int i=0; i< A.size(); i++){
                for(int j=0; j<A[0].size(); j++){
                    AA[j][i] = A[i][j];
                    AA[j+n][i] = (-1.0) * A[i][j];
                }
            }
            
            for(int i=0; i< m; i++){
                AA[i+2*n][i] = -1;
            }
            for(int i=0; i<m; i++){
                AA[2*n+m][i] = b[i];
            }


        vector<double> bb(2*n+m+1, 0.0);
        //initialiste the new rhs
            bb[2*n+m] = -1;

        // this is now the same as before..
        vector<Matrix_Vector_Set> everything_important2(m);
        
        for(int j=0; j<m; j++ ){
            // Eliminate all Variables and save the produced part-solutions
            Matrix_Vector_Set construct2 = Fourier_motzkin(AA, bb, j);
            everything_important2[j].Matrix = AA;
            everything_important2[j].Vector = bb;
            everything_important2[j].Set = construct2.Set;
            AA = construct2.Matrix;
            bb = construct2.Vector;
        }

     
        if (is_valid(bb)){
            // the feasable vector for the new LP is our certificate vector
            calculate_feasable_vector(everything_important2);
        } else{
          cout << "No solution\n";
          exit(0);
        }
        
    }
}