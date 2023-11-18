Pt start(0, 0);

bool comp(Pt a, Pt b) {
    ll ang = (a - start).cross(b - start);
    if (ang < 0) {
        return false;
    } else if (ang > 0) {
        return true;
    }
    return abs(start - a) < abs(start - b);
}

vector<Pt> convex_hull(vector<Pt> points) {
    int n = points.size();
    start = points[0];
    for (auto x : points) {
        start = min(start, x);
    }
    sort(points.begin(), points.end(), comp);
    vector<Pt> s = {points[0], points[1]};
    for (int i = 2; i < n; i++) {
        int k = s.size();
        while (k > 1 && (s[k - 1] - s[k - 2]).cross(points[i] - s[k - 1]) <= 0) {
            s.pop_back();
            k = s.size();
        }
        s.push_back(points[i]);
    }
    return s;
}


