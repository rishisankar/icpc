// doesn't work :(

#include <bits/stdc++.h>
using namespace std;

#define PI 3.1415926535897932384626433832795
#define MOD 1000000007
#define FOR(i, j, k) for (int i=j ; i<k ; ++i)
#define FORI(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k) for (int i=j ; i>=k ; --i)
#define RFORI(i, j, k, in) for (int i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j)
#define RREP(i, j) RFOR(i, j, 0)
#define OREP(i, j) FOR(i, 1, j+1)
#define all(cont) cont.begin(), cont.end()
#define PB push_back

template<typename T> inline T maxe(vector<T> &vec) { return *max_element(all(vec)); }
template<typename T> inline T mine(vector<T> &vec) { return *min_element(all(vec)); }

template<typename T> inline void printV(vector<T> &vec) {
    cout << "########\n";
    for (int i = 0; i < vec.size(); ++i) {
        cout << vec[i] << ' ';
    }
    cout << '\n';
    cout << "########\n";
}
template<typename T> inline void printVV(vector<vector<T>> &vec) {
    cout << "########\n";
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = 0; j < vec[i].size(); ++j) {
            cout << vec[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << "########\n";
}

typedef long long ll;
typedef long double ld;
typedef vector<int> VI;
typedef vector<vector<int>> VVI;
typedef vector<bool> VB;
typedef vector<vector<bool>> VVB;
typedef vector<string> VS;
typedef vector<vector<string>> VVS;
typedef pair<int, int> PII;

struct Interval {
    ld start, end; 

    Interval(ld start_, ld end_) : start(start_), end(end_) {}
};

bool compareInterval(Interval i1, Interval i2) { 
    return (i1.start < i2.start); 
} 

void mergeIntervals(vector<Interval>& vec, vector<Interval>& res) { 
    int n = vec.size();
    if (n <= 0) return; 

    sort(vec.begin(), vec.end(), compareInterval);
    res.push_back(vec[0]);
    int curIndex = 0;
    ld curEnd = vec[0].end;
    for (int i = 1; i < n; ++i) {
        Interval cur = vec[i];
        if (cur.start > curEnd) {
            res.push_back(cur);
            curEnd = cur.end;
            ++curIndex;
        } else {
            curEnd = max(curEnd, cur.end);
            res[curIndex].end = curEnd;
        }
    }
} 

struct Circle {

    ld r;
    ld x;
    ld y;
    ll lr;
    ll lx;
    ll ly;

    Circle(ll X, ll Y, ll R) : x(X), y(Y), r(R), lx(X), ly(Y), lr(R) {}
    
    // add intervals of angles around c1 contained inside c2
    void interval(Circle c2, vector<Interval>& intervals) {
        ll dx = c2.lx - lx;
        ll dy = c2.ly - ly;
        ll ns = dx*dx + dy*dy;
        if (ns >= (lr + c2.lr)*(lr + c2.lr)) return;
        if (ns == 0) {
            if (lr <= c2.lr) {
                Interval full(0, 2*PI);
                intervals.push_back(full);
                return;
            } else {
                return;
            }
        }

        ld cdist = sqrt(ns);
        if (max(lr, c2.lr) >= cdist + min(lr, c2.lr)) {
            Interval full(0, 2*PI);
            intervals.push_back(full);
            return;
        }

        ld xangle = atan2(dy, dx); if (xangle < 0) xangle += 2*PI;

        ld cosalphaNum = lr*lr + ns - c2.lr*c2.lr;
        ld cosalpha = cosalphaNum / (2*lr*sqrt(ns));
        ld alpha = acos(cosalpha);

        ld beginAngle = xangle - alpha;
        ld endAngle = xangle + alpha;
        if (beginAngle < 0) beginAngle += 2*PI;
        if (endAngle < 0) endAngle += 2*PI;
        if (beginAngle > 2*PI) beginAngle -= 2*PI;
        if (endAngle > 2*PI) endAngle -= 2*PI;

        if (endAngle >= beginAngle) {
            Interval i(beginAngle, endAngle);
            intervals.push_back(i);
        } else {
            Interval i1(beginAngle, 2*PI);
            Interval i2(0, endAngle);
            intervals.push_back(i1);
            intervals.push_back(i2);
        }
        
    }
     
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.setf(ios::fixed);
    cout.precision(10);

    int n; cin >> n;

    vector<Circle> circles;
    REP(i, n) {
        ll x,y,r;
        cin >> x >> y >> r;
        Circle circ(x, y, r);
        circles.push_back(circ);
    }
    reverse(circles.begin(), circles.end());

    ld totalResult = 0;

    REP(i, n) {
        vector<Interval> intervals;
        REP(j, i) {
            circles[i].interval(circles[j], intervals);
        }

        vector<Interval> merged;
        mergeIntervals(intervals, merged);

        ld total = 2*PI;
        for (Interval inte : merged) {
            total -= (inte.end - inte.start);
        }
        ld arclength = total*circles[i].lr;

        totalResult += arclength;
    }

    cout << totalResult << '\n';

    // vector<Interval> intervals;
    // Interval i1(1, 2.5);
    // Interval i2(-1, 1);
    // Interval i3(-5,-2);
    // Interval i4(7,9.3);
    // Interval i5(8, 11);
    // //Interval i6(1.3, 15);
    // intervals.push_back(i1);
    // intervals.push_back(i2);
    // intervals.push_back(i3);
    // intervals.push_back(i4);
    // intervals.push_back(i5);
    // //intervals.push_back(i6);
    // vector<Interval> merged;
    // mergeIntervals(intervals, merged);
    // cout << "Intervals:\n";
    // for (Interval i : merged) {
    //     cout << i.start << " " << i.end << '\n';
    // }

}