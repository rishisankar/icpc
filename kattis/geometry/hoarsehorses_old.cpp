#include <bits/stdc++.h>
using namespace std;

struct ls {
    long long x1;
    long long y1;
    long long x2;
    long long y2;
};

bool parallel(ls l1, ls l2) {

    if (l1.y1 == l1.y2) {
        return l2.y1 == l2.y2;
    }
    if (l2.x1 == l2.x2) {
        return l1.x1 == l1.x2;
    }

    return ((l1.y2 - l1.y1) * (l2.x2 - l2.x1) == (l2.y2 - l2.y1) * (l1.x2 - l1.x1));

}

bool yint(ls l1, ls l2) {

    if (l1.x2 - l1.x1 == 0) {
        return l1.x1 == l2.x1;
    }

    long long a1 = ((l1.y2 - l1.y1)*(-l1.x1)+(l1.x2 - l1.x1)*(l1.y1)) * (l2.x2 - l2.x1);
    long long a2 = ((l2.y2 - l2.y1)*(-l2.x1)+(l2.x2 - l2.x1)*(l2.y1)) * (l1.x2 - l1.x1);

    return a1 == a2;

}

bool sharevertex(ls l1, ls l2) {
    if (l1.x1 == l2.x1 && l1.y1 == l2.y1) {
        return true;
    }
    if (l1.x2 == l2.x1 && l1.y2 == l2.y1) {
        return true;
    }
    if (l1.x2 == l2.x2 && l1.y2 == l2.y2) {
        return true;
    }
    if (l1.x1 == l2.x2 && l1.y1 == l2.y2) {
        return true;
    }
    return false;
}

/*
    0: not within
    2: on edge
    3: inside
*/
int within(long long x, long long a, long long b) {
    long long am = min(a,b);
    long long ma = max(a,b);
    if (x == a || x == b) {
        return 2;
    }
    if (am < x && x < ma) {
        return 3;
    }
    return 0;
}

/*
    0: no intersection
    1: shared vertex
    2: side intersection
    3: regular intersection
*/
int intersection(ls l1, ls l2) {

    if (sharevertex(l1,l2)) {
        return 1;
    }


    // avoid multiply by 0 mistakes
    if (l1.x1 == l1.x2 && l2.x1 == l2.x2) {
        return 0;
    }
    if (l1.x1 == l1.x2) {
        long long ay = (l2.y2 - l2.y1)*(l1.x1 - l2.x1) + l2.y1*(l2.x2-l2.x1);
        return within(ay, l1.y1*(l2.x2-l2.x1), l1.y2*(l2.x2-l2.x1));
    }
    if (l2.x1 == l2.x2) {
        long long ay = (l1.y2 - l1.y1)*(l2.x1 - l1.x1) + l1.y1*(l1.x2-l1.x1);
        return within(ay, l2.y1*(l1.x2-l1.x1), l2.y2*(l1.x2-l1.x1));
    }

    //long long ax = (l1.x2 - l1.x1)*(l2.x2 - l2.x1) + (l1.x1) * (l1.y2 - l1.y1) * (l2.x2 - l2.x1) - (l2.x1) * (l2.y2 - l2.y1) * (l1.x2 - l1.x1);
    //long long sc = (l1.y2 - l1.y1) * (l2.x2 - l2.x1) - (l2.y2 - l2.y1) * (l1.x2 - l1.x1);

    long long sc = (l1.x1 - l1.x2) * (l2.y1 - l2.y2) + (l1.y1) * (l2.x2 - l2.x1) + (l1.y2) * (l2.x1 - l2.x2);
    long long ax = (l1.x1)*(l1.y2*l2.x1 - l1.y2*l2.x2 - l2.x1*l2.y2 + l2.y1*l2.x1) + l1.y1 * l1.x2 * (l2.x2 - l2.x1) + l1.x2 * l2.x1 * l2.y2 - l1.x2 * l2.y1 * l2.x2;

    //printf("ax: %d, sc: %d\n", ax, sc);

    if (sc * l1.x1 == ax) return 2;
    if (sc * l1.x2 == ax) return 2;
    if (sc * l2.x1 == ax) return 2;
    if (sc * l2.x2 == ax) return 2;

    if (sc >= 0) {
        if (sc * l1.x1 < ax && ax < sc * l1.x2) {
            if (sc * l2.x1 < ax && ax < sc * l2.x2) {
                return 3;
            }
        }
        return 0;
    } else {
        if (sc * l1.x2 < ax && ax < sc * l1.x1) {
            if (sc * l2.x2 < ax && ax < sc * l2.x1) {
                return 3;
            }
        }
        return 0;
    }

    return 0;

}

int main() {

    int n;
    cin >> n;

    ls segs[1001];

    for (int i = 0; i < n; ++i) {
        cin >> segs[i].x1 >> segs[i].y1 >> segs[i].x2 >> segs[i].y2;
        if (segs[i].x1 > segs[i].x2) {
            long long tmpx = segs[i].x1;
            long long tmpy = segs[i].y1;
            segs[i].x1 = segs[i].x2;
            segs[i].y1 = segs[i].y2;
            segs[i].x2 = tmpx;
            segs[i].y2 = tmpy;
        }
    }

    // get rid of overlapping lines (colinear + share a point)
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {

            if (segs[i].x1 == segs[i].x2 || segs[j].x1 == segs[j].x2) {
                if (segs[i].x1 == segs[i].x2 && segs[j].x1 == segs[j].x2) {
                    if (segs[i].x1 == segs[j].x1) {
                        if ((max(segs[i].y1, segs[i].y2) >= min(segs[j].y1,segs[j].y2) && max(segs[i].y1, segs[i].y2) <= max(segs[j].y1,segs[j].y2)) ||
                            (min(segs[i].y1, segs[i].y2) >= min(segs[j].y1,segs[j].y2) && min(segs[i].y1, segs[i].y2) <= max(segs[j].y1,segs[j].y2))) {
                                segs[i].y1 = min(min(segs[i].y1, segs[i].y2), min(segs[j].y1,segs[j].y2));
                                segs[i].y2 = max(max(segs[i].y1, segs[i].y2), max(segs[j].y1,segs[j].y2));
                                segs[j].x1 = segs[n-1].x1;
                                segs[j].x2 = segs[n-1].x2;
                                segs[j].y1 = segs[n-1].y1;
                                segs[j].y2 = segs[n-1].y2;
                                //printf("Found overlap: i=%d,j=%d\n", i, j);
                                --n;
                                --j;
                            }
                    }
                }
            } else {
                if (parallel(segs[i], segs[j]) && yint(segs[i],segs[j])) {
                    if ((segs[i].x1 >= segs[j].x1 && segs[i].x1 <= segs[j].x2) ||
                        (segs[i].x2 >= segs[j].x1 && segs[i].x2 <= segs[j].x2) ||
                        (segs[j].x2 >= segs[i].x1 && segs[j].x2 <= segs[i].x2) ||
                        (segs[j].x1 >= segs[i].x1 && segs[j].x1 <= segs[i].x2)) {
                        if (segs[i].x1 > segs[j].x1) {
                            segs[i].x1 = segs[j].x1;
                            segs[i].y1 = segs[j].y1;
                        }
                        if (segs[i].x2 < segs[j].x2) {
                            segs[i].x2 = segs[j].x2;
                            segs[i].y2 = segs[j].y2;
                        }
                        segs[j].x1 = segs[n-1].x1;
                        segs[j].x2 = segs[n-1].x2;
                        segs[j].y1 = segs[n-1].y1;
                        segs[j].y2 = segs[n-1].y2;
                        //printf("Found overlap 2: i=%d,j=%d\n", i, j);
                        --n;
                        --j;
                    }
                }
            }

        }
    }

    int count = 0;

    while (n > 0) {

        vector<ls> vec;
        vec.push_back(segs[n-1]);
        queue<ls> q;
        q.push(segs[n-1]);
        n--;

        while (!q.empty()) {

            ls top = q.front();
            q.pop();

            for (int i = n-1; i >= 0; --i) {
                if (intersection(top, segs[i]) != 0) {
                    vec.push_back(segs[i]);
                    q.push(segs[i]);
                    segs[i] = segs[n-1];
                    n--;
                }
            }

        }

        long long sz = vec.size();
        // for (ls l : vec) {
        //     printf("Line Segment: %d %d %d %d \n", l.x1,l.y1,l.x2,l.y2);
        // }
        long long vertices = 2 * sz;
        long long edges = sz;
        for (int i = 0; i < sz; ++i) {
            for (int j = i+1; j < sz; ++j) {
                int inter = intersection(vec[i], vec[j]);
                //printf("(%d,%d)-(%d,%d) and (%d,%d)-(%d,%d) :  intersection=%d\n", vec[i].x1, vec[i].y1, vec[i].x2, vec[i].y2, vec[j].x1, vec[j].y1, vec[j].x2, vec[j].y2, inter);
                if (inter == 3) {
                    ++vertices;
                }
                else if (inter == 1) {
                    --vertices; 
                }

                if (inter == 2) {
                    ++edges;
                }  
                else if (inter == 3) {
                    edges += 2;
                }
            }
        }

        long long faces = 2 + edges - vertices;

        count += faces - 1;

    }

    cout << count << '\n';
}