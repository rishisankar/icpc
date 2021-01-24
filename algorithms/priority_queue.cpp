// example of priority queue usage: graphs/emptyingbaltic

#include <bits/stdc++.h>
using namespace std;

int h,w;

bool outOfBounds(int x, int y) {
    return x < 0 || y < 0 || x >= h || y >= w;
}

struct point {
    int x;
    int y;
    int alt;
};

struct Compare
{
    bool operator() (const point& p1, const point& p2) {
        return p1.alt < p2.alt;
    }
};

int main() {

    
    cin >> h >> w;

    vector<vector<int>> alts(h, vector<int>(w));
    vector<vector<bool>> visited(h, vector<bool>(w, false));

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            cin >> alts[i][j];
            if (alts[i][j] > 0) alts[i][j] = 0;
            alts[i][j] *= -1;
        }
    }

    int cx, cy;
    cin >> cx >> cy;
    cx--; cy--;

    long long count = 0;

    priority_queue<point, vector<point>, Compare> pq;
    point center;
    center.x = cx;
    center.y = cy;
    center.alt = alts[cx][cy];
    pq.push(center);

    while (!pq.empty()) {
        point t = pq.top();
        pq.pop();
        if (visited[t.x][t.y]) continue;
        visited[t.x][t.y] = true;
        count += t.alt;
        for (int x = t.x - 1; x <= t.x+1; ++x) {
            for (int y = t.y - 1; y <= t.y+1; ++y) {
                if (outOfBounds(x,y) || visited[x][y]) continue;
                if (alts[x][y] <= 0) continue;
                point tmp;
                tmp.x=x;
                tmp.y=y;
                tmp.alt = min(alts[x][y], t.alt);
                pq.push(tmp);
            }
        }
    }
    
    cout << count << '\n';
}