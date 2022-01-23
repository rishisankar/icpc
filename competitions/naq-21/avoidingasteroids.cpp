#include <bits/stdc++.h>
using namespace std;

#define PI 3.1415926535897932384626433832795
#define MOD 1000000007
#define FOR(i, j, k) for (int i=j ; i<k ; ++i)
#define rep(i, a, b) for(int i = a; i < (b); ++i) 
#define FORI(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k) for (int i=j ; i>=k ; --i)
#define RFORI(i, j, k, in) for (int i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j)
#define RREP(i, j) RFOR(i, j, 0)
#define OREP(i, j) FOR(i, 1, j+1)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back
#define F first
#define S second
#define INP(v, n) for (int i=0; i<n; ++i) { cin >> v[i]; }
#define ceil(x) (ll)ceil(x)
#define floor(x) (ll)floor(x)

template<typename T> inline T maxe(vector<T> &vec) { return *max_element(all(vec)); }
template<typename T> inline T mine(vector<T> &vec) { return *min_element(all(vec)); }

template<typename T> inline void printV(vector<T> &vec) {
    cerr << "########\n";
    for (int i = 0; i < vec.size(); ++i) {
        cerr << vec[i] << ' ';
    }
    cerr << '\n';
    cerr << "########\n";
}
template<typename T> inline void printVV(vector<vector<T>> &vec) {
    cerr << "########\n";
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = 0; j < vec[i].size(); ++j) {
            cerr << vec[i][j] << ' ';
        }
        cerr << '\n';
    }
    cerr << "########\n";
}
template<typename T> inline void print(T obj) { cout << obj << '\n'; }
template<typename T, typename... Args> inline void print(T t, Args... args) { cout << t << " "; print(args...); }
template<typename T> inline void dbg(T obj) { cerr << obj << '\n'; }
template<typename T, typename... Args> inline void dbg(T t, Args... args) { cerr << t << " "; dbg(args...); }

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef vector<int> VI;
typedef vector<int> vi; 
typedef vector<vector<int>> VVI;
typedef vector<long long> VLL;
typedef vector<vector<long long>> VVLL;
typedef vector<bool> VB;
typedef vector<vector<bool>> VVB;
typedef vector<string> VS;
typedef vector<vector<string>> VVS;
typedef pair<int, int> PII;
typedef pair<int, int> pii;
typedef vector<pair<int, int>> VPII;
typedef vector<vector<pair<int, int>>> VVPII;

double x1,y11,z1,x2,y2,z2; // endpts of line segment
double x,y,z,vx,vy,vz,r; // starting point, direction, radius of ray

// x between 0 and 1
double f(double i) {
    double nx = x1 + i*(x2-x1);
    double ny = y11 + i*(y2-y11);
    double nz = z1 + i*(z2-z1);

    // projection of point on line: A + dot(AP,AB) / dot(AB,AB) * AB
    double dAB = vx*vx+vy*vy+vz*vz;
    double dAP = (nx-x)*vx + (ny-y)*vy + (nz-z)*vz;
    double px = x + dAP/dAB*vx;
    double py = y + dAP/dAB*vy;
    double pz = z + dAP/dAB*vz;
    double dt = (x-px)*vx + (y-py)*vy + (z-pz)*vz;

    // dbg("pt on line seg",nx,ny,nz);
    // dbg("ray center",x,y,z);
    // dbg("AB",vx,vy,vz);
    // dbg("dot prods",dAB,dAP);
    // dbg("proj",px,py,pz);
    // dbg("vector dp",dt);
    if (dt > 0) {
        // projection not on ray --> take distance to endpt of ray
        return -sqrt((nx-x)*(nx-x) + (ny-y)*(ny-y) + (nz-z)*(nz-z));
    } else {
        // projection on ray --> take distance to projection
        return -sqrt((nx-px)*(nx-px) + (ny-py)*(ny-py) + (nz-pz)*(nz-pz));
    }
}

double ternary_search(double l, double r) {
    double eps = 1e-9;              //set the error limit here
    while (r - l > eps) {
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        double f1 = f(m1);      //evaluates the function at m1
        double f2 = f(m2);      //evaluates the function at m2
        if (f1 < f2)
            l = m1;
        else
            r = m2;
    }
    return -f(l);                    //return the maximum of f(x) in [l, r]
}

void run() {
	cin >> x1 >> y11 >> z1;
	cin >> x2 >> y2 >> z2;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		double px, py, pz;
		cin >> px >> py >> pz;
		double dx, dy, dz;
		cin >> dx >> dy >> dz;
		int m;
		cin >> m;
		double dist = 0;
		for (int j = 0; j < m; j++) {
			double cx, cy, cz;
			cin >> cx >> cy >> cz;
			dist = max(dist,
					(cx - px) * (cx - px) + (cy - py) * (cy - py)
							+ (cz - pz) * (cz - pz));
		}
        x=px;y=py;z=pz;
        vx=dx;vy=dy;vz=dz;
		r = sqrt(dist);

        double opt = ternary_search(0, 1);
        if (opt < r) {
            print("Surrender");
            return;
        }

	}
    print("Go");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(10);
    // ll t; cin >> t;
    ll t=1;
    REP(tests,t) run();
}