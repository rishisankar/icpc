// shoelace algorithm: tells if coordinates are in CW or CCW orientation and gives polygon area
// O(n), example geometry/polygonarea
// return: (true if clockwise, polygon area)
pair<bool, double> shoelace(vector<pair<int, int>> coords) {
    double area = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i+1)%n;
        area += (v[i].first + v[j].first) * (v[i].second - v[j].second);
    }
    area/=2;
    return {area >= 0, abs(area)};
}
