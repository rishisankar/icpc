// doesn't work!

#include <bits/stdc++.h>
using namespace std;

#define PI 3.1415926535897932384626433832795

struct glass {
    int x;
    int y;
    int z;
    int r;
    int v;
};

double dist(glass g1, glass g2) {
    double d = (g1.x-g2.x)*(g1.x-g2.x) + (g1.y-g2.y)*(g1.y-g2.y);
    return sqrt(d);
}

int main() {
    int n;
    cin >> n;
    vector<glass> vec(n);
    for (int i = 0; i < n; ++i) {
        int x,y,z,r,v;
        cin >> x >> y >> z >> r >> v;
        vec[i].x = x; vec[i].y = y; vec[i].z = z; vec[i].r = r; vec[i].v = v;
    }

    // sort?

    vector<vector<double>> adj(n, vector<double>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (vec[i].z <= vec[j].z) continue;
            double d = dist(vec[i], vec[j]);
            if (d > vec[i].r && d > vec[j].r && d < vec[i].r + vec[j].r) {
                glass top = vec[i];
                glass bottom = vec[j];
                double d = d*d + top.z*top.z - bottom.z*bottom.z;
                d /= 2*d*top.z;
                double len = acos(d)/2/PI;
                adj[i][j] = len;
            }
        }
    }

    

}