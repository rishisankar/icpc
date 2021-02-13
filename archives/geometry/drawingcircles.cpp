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

struct Interval 
{ 
    ld start, end; 
};

// Compares two intervals according to their staring time. 
// This is needed for sorting the intervals using library 
// function std::sort(). See http://goo.gl/iGspV 
bool compareInterval(Interval i1, Interval i2) 
{ 
    return (i1.start < i2.start); 
} 
  
// The main function that takes a set of intervals, merges 
// overlapping intervals and prints the result 
void mergeIntervals(vector<Interval>& arr, vector<Interval>& res) 
{ 
    int n = arr.size();
    // Test if the given set has at least one interval 
    if (n <= 0) 
        return; 
  
    // Create an empty stack of intervals 
    stack<Interval> s; 
  
    // sort the intervals in increasing order of start time 
    sort(arr.begin(), arr.end(), compareInterval); 
  
    // push the first interval to stack 
    s.push(arr[0]); 
  
    // Start from the next interval and merge if necessary 
    for (int i = 1 ; i < n; i++) 
    { 
        // get interval from stack top 
        Interval top = s.top(); 
  
        // if current interval is not overlapping with stack top, 
        // push it to the stack 
        if (top.end < arr[i].start) 
            s.push(arr[i]); 
  
        // Otherwise update the ending time of top if ending of current 
        // interval is more 
        else if (top.end < arr[i].end) 
        { 
            top.end = arr[i].end; 
            s.pop(); 
            s.push(top); 
        } 
    } 
  
    while (!s.empty()) 
    { 
        Interval t = s.top(); 
        res.push_back(t);
        s.pop(); 
    } 
    return; 
} 

class Point2d{
public:
    Point2d() {}
    Point2d(ld x, ld y)
        : X(x), Y(y) {}
     
    ld x() const { return X; }
    ld y() const { return Y; }
     
    /**
     * Returns the norm of this vector.
     * @return the norm
    */
    ld norm() const {
        return sqrt( X * X + Y * Y );
    }
     
    void setCoords(ld x, ld y) {
        X = x; Y = y;
    }
     
    // Print point
    friend std::ostream& operator << ( std::ostream& s, const Point2d& p )  {
      s << p.x() << " " << p.y();
      return s;
    }

    Point2d operator-(const Point2d& p) const { return Point2d(X - p.x(), Y - p.y()); }
    ld cross(const Point2d& p) const { return X * p.y() - Y * p.x(); }
    ld cross(const Point2d& a, const Point2d& b) const { return (a - *this).cross(b - *this); }

private:
    ld X;
    ld Y;
};
 
// use check_inter to check if the line segments given by AB and CD intersect.
// source: https://cp-algorithms.com/geometry/check-segments-intersection.html


int sgn(const ld& x) { return x >= 0 ? x ? 1 : 0 : -1; }

bool inter1(ld a, ld b, ld c, ld d) {
    if (a > b)
        swap(a, b);
    if (c > d)
        swap(c, d);
    return max(a, c) <= min(b, d);
}

bool check_inter(const Point2d& a, const Point2d& b, const Point2d& c, const Point2d& d) {
    if (c.cross(a, d) == 0 && c.cross(b, d) == 0)
        return inter1(a.x(), b.x(), c.x(), d.x()) && inter1(a.y(), b.y(), c.y(), d.y());
    return sgn(a.cross(b, c)) != sgn(a.cross(b, d)) &&
           sgn(c.cross(d, a)) != sgn(c.cross(d, b));
}


class Circle{
public:
    /**
     * @param R - radius
     * @param X - center's x coordinate
     * @param Y - center's y coordinate
     */
    Circle(ll R, ll X, ll Y) 
        : r(R), c(X, Y), lr(R), lx(X), ly(Y) {}    
     
    Point2d getC() const { return c; }
    ld getR() const { return r; }

    bool in_circle(Point2d& p) {
        ld d = Point2d(c.x() - p.x(), c.y() - p.y()).norm();
        return d <= r;
    }
     
    size_t intersect(const Circle& C2, Point2d& i1, Point2d& i2) {
        // distance between the centers
        ld d = Point2d(c.x() - C2.c.x(), 
                c.y() - C2.c.y()).norm();
         
        // find number of solutions
        if(d > r + C2.r) // circles are too far apart, no solution(s)
        {
            //std::cout << "Circles are too far apart\n";
            return 0;
        }
        else if(d == 0 && r == C2.r) // circles coincide
        {
            //std::cout << "Circles coincide\n";
            return 0;
        }
        // one circle contains the other
        else if(d + min(r, C2.r) < max(r, C2.r))
        {
            //std::cout << "One circle contains the other\n";
            return 0;
        }
        else
        {
            ld a = (r*r - C2.r*C2.r + d*d)/ (2.0*d);
            ld h = sqrt(r*r - a*a);
             
            // find p2
            Point2d p2( c.x() + (a * (C2.c.x() - c.x())) / d,
                    c.y() + (a * (C2.c.y() - c.y())) / d);
             
            // find intersection points p3
            i1.setCoords( p2.x() + (h * (C2.c.y() - c.y())/ d),
                    p2.y() - (h * (C2.c.x() - c.x())/ d)
            );
            i2.setCoords( p2.x() - (h * (C2.c.y() - c.y())/ d),
                    p2.y() + (h * (C2.c.x() - c.x())/ d)
            );
             
            if(d == r + C2.r)
                return 1;
            return 2;
        }
    }

    void addInterval(ld start, ld end, vector<Interval>& intervals, bool small) {
        ld len = 0;
        if (start > end) {
            len = 2*PI - (start - end);
        } else {
            len = end - start;
        }
        if ((len > PI && small) || (len < PI && (!small))) {
            swap(start, end);
        }
        if (end > start) {
            Interval i;
            i.start = start;
            i.end = end;
            intervals.push_back(i);
        } else {
            Interval i1, i2;
            i1.start = start;
            i1.end = 2*PI;
            i2.start = 0;
            i2.end = end;
            intervals.push_back(i1);
            intervals.push_back(i2);
        }
    }

    ld getAngle(Point2d pt) {
        ld dx = pt.x() - c.x();
        ld dy = pt.y() - c.y();
        ld angle = atan2(dy, dx);
        if (angle < 0) angle += 2*PI;
        return angle;
    }

    // add intervals of angles around c1 contained inside c2
    void interval(Circle c2, vector<Interval>& intervals) {
        ll dx = c2.lx - lx;
        ll dy = c2.ly - ly;
        ll ns = dx*dx + dy*dy;
        if (ns >= (lr + c2.lr)*(lr + c2.lr)) return;
        if (ns == 0) {
            if (lr <= c2.lr) {
                Interval full;
                full.start = 0;
                full.end = 2*PI;
                intervals.push_back(full);
                return;
            } else {
                return;
            }
        }
        // Point2d p1, p2;
        // int res = this->intersect(c2, p1, p2);
        // if (res == 0 || res == 1) {
        //     Point2d sample(c.x() + r, c.y());
        //     Point2d sample2(c.x() - r, c.y());
        //     if (c2.in_circle(sample) && c2.in_circle(sample2)) {
        //         Interval full;
        //         full.start = 0;
        //         full.end = 2*PI;
        //         intervals.push_back(full);
        //         return;
        //     } else {
        //         return;
        //     }
        // }

        ld cdist = sqrt(ns);
        if (max(lr, c2.lr) >= cdist + min(lr, c2.lr)) {
            Interval full;
            full.start = 0;
            full.end = 2*PI;
            intervals.push_back(full);
            return;
        }


        // ld a1 = this->getAngle(p1);
        // ld a2 = this->getAngle(p2);
        
        // bool small = false;
        // if (check_inter(p1, p2, c, c2.c)) {
        //     small = true;
        // }
        //
        // this->addInterval(a1, a2, intervals, small);

        ld xangle = atan2(dy ,dx); if (xangle < 0) xangle += 2*PI;
        //cout << "XANGLE: " << xangle << '\n';
        //cout << "params " << lr << " " << ns << " " << c2.lr << '\n';
        ll cosalphaNum = lr*lr + ns - c2.lr*c2.lr;
        ld den = 2.0;
        ld s1 = lr;
        ld s2 = sqrt(ns);
        ld cosalpha = cosalphaNum / den / s1 / s2;
        //cout << "cos " << cosalpha << '\n';
        ld alpha = acos(cosalpha);
        ld beginAngle = xangle - alpha;
        ld endAngle = xangle + alpha;
        //cout << "begin: " << beginAngle << " , end: " << endAngle << '\n'; 
        if (beginAngle < 0) beginAngle += 2*PI;
        if (endAngle < 0) endAngle += 2*PI;
        if (beginAngle > 2*PI) beginAngle -= 2*PI;
        if (endAngle > 2*PI) endAngle -= 2*PI;
        if (endAngle >= beginAngle) {
            Interval i;
            i.start = beginAngle;
            i.end = endAngle;
            intervals.push_back(i);
        } else {
            Interval i1, i2;
            i1.start = beginAngle;
            i1.end = 2*PI;
            i2.start = 0;
            i2.end = endAngle;
            intervals.push_back(i1);
            intervals.push_back(i2);
        }

        
        
    }
     
    // Print circle
    friend std::ostream& operator << ( std::ostream& s, const Circle& C )  {
      s << "Center: " << C.getC() << ", r = " << C.getR();
      return s;
    }

    // radius
    ld r;
    // center
    Point2d c;

    ll lr;
    ll lx;
    ll ly;
     
};




int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.setf(ios::fixed);
    cout.precision(10);

    int n; cin >> n;

    vector<Circle> circles;
    REP(i, n) {
        ld x,y,r;
        cin >> x >> y >> r;
        Circle circ(r,x,y);
        circles.push_back(circ);
    }
    reverse(circles.begin(), circles.end());

    ld totalResult = 0;

    REP(i, n) {
        vector<Interval> intervals;
        REP(j, i) {
            circles[i].interval(circles[j], intervals);
        }
        // for (Interval inter : intervals) {
        //     cout << i << " " << inter.start << " " << inter.end << '\n';
        // }
        vector<Interval> merged;
        mergeIntervals(intervals, merged);

        ld total = 2*PI;
        for (Interval inte : merged) {
            total -= (inte.end - inte.start);
        }
        ld arclength = total*circles[i].getR();

        totalResult += arclength;
    }

    cout << totalResult << '\n';

    // ld x1, y1, r1; cin >> x1 >> y1 >> r1;
    // ld x2, y2, r2; cin >> x2 >> y2 >> r2;

    // Circle c1(r1,x1,y1);
    // Circle c2(r2,x2,y2);

    // Point2d p1, p2;
    // cout << c1.intersect(c2, p1, p2) << '\n';
    // cout << p1.x() << " " << p1.y() << "\n";
    // cout << p2.x() << " " << p2.y() << "\n";
    // cout << c1.getAngle(p1) << " " << c1.getAngle(p2) << "\n";
    
    // vector<Interval> intervals;
    // c1.interval(c2, intervals);
    // vector<Interval> merged;
    // mergeIntervals(intervals, merged);
    // cout << "Intervals:\n";
    // for (Interval i : merged) {
    //     cout << i.start << " " << i.end << '\n';
    // }


}