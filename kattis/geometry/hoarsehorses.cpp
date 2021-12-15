#include <bits/stdc++.h>
using namespace std;

struct pt {
    long long x, y;
    pt() {}
    pt(long long _x, long long _y) : x(_x), y(_y) {}
    pt operator-(const pt& p) const { return pt(x - p.x, y - p.y); }
    long long cross(const pt& p) const { return x * p.y - y * p.x; }
    long long cross(const pt& a, const pt& b) const { return (a - *this).cross(b - *this); }
};

int sgn(const long long& x) { return x >= 0 ? x ? 1 : 0 : -1; }

bool inter1(long long a, long long b, long long c, long long d) {
    if (a > b)
        swap(a, b);
    if (c > d)
        swap(c, d);
    return max(a, c) <= min(b, d);
}

bool check_inter(const pt& a, const pt& b, const pt& c, const pt& d) {
    if (c.cross(a, d) == 0 && c.cross(b, d) == 0)
        return inter1(a.x, b.x, c.x, d.x) && inter1(a.y, b.y, c.y, d.y);
    return sgn(a.cross(b, c)) != sgn(a.cross(b, d)) &&
           sgn(c.cross(d, a)) != sgn(c.cross(d, b));
}

struct ls {
    long long x1;
    long long y1;
    long long x2;
    long long y2;
};

bool intersection(ls l1, ls l2) {
    pt a(l1.x1, l1.y1);
    pt b(l1.x2, l1.y2);
    pt c(l2.x1, l2.y1);
    pt d(l2.x2, l2.y2);

    return check_inter(a,b,c,d);
}

int main() {

    int n;
    cin >> n;
    int N = n;

    ls segs[1001];

    for (int i = 0; i < n; ++i) {
        cin >> segs[i].x1 >> segs[i].y1 >> segs[i].x2 >> segs[i].y2;
    }

    long long intersections = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (intersection(segs[i],segs[j])) {
                ++intersections;
            }
        }
    }

    long long count = 0;

    while (n > 0) {

        queue<ls> q;
        q.push(segs[n-1]);
        n--;

        while (!q.empty()) {

            ls top = q.front();
            q.pop();

            for (int i = n-1; i >= 0; --i) {
                if (intersection(top, segs[i])) {
                    q.push(segs[i]);
                    segs[i] = segs[n-1];
                    n--;
                }
            }

        }

        ++count;

    }

    cout << count - N + intersections << '\n';
}