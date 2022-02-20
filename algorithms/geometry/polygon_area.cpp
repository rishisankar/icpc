// shoelace algorithm: tells if coordinates are in CW or CCW orientation and gives polygon area
// O(n), example geometry/polygonarea
// return: (true if clockwise, polygon area)
pair<bool, double> shoelace(vector<pair<int, int>> v) {
    double area = 0;
    for (int i = 0; i < v.size(); ++i) {
        int j = (i+1)%v.size();
        area += (v[i].first + v[j].first) * (v[i].second - v[j].second);
    }
    area/=2;
    return {area >= 0, abs(area)};
}
