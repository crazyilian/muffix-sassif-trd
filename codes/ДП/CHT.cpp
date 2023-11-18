pair<ld, ld> inter(Line a, Line b) {
    ld x = (b.b - a.b) / (a.k - b.k);
    ld y = a.k * x + a.b;
    return {x, y};
}
 
void add_line(ld k, ld b, vector<Line> &s, vector<pair<ld, ld>> &pts) {
    while (s.size() >= 2) {
        pair<ld, ld> x1 = inter(s.back(), s[s.size() - 2]);
        pair<ld, ld> x2 = inter(s[s.size() - 2], {k, b});
        if (x1 > x2) {
            break;
        }
        pts.pop_back();
        s.pop_back();
    }
    if (!s.empty()) {
        pts.push_back(inter(s.back(), {k, b}));
    }
    s.push_back({k, b});
}
 
ld bin_search(vector<Line> &s, ld x) {
    int l = 0, r = s.size();
    while (l + 1 < r) {
        int m = (r + l) / 2;
        auto kek = inter(s[m - 1], s[m]);
        if (kek.first >= x) {
            l = m;
        } else {
            r = m;
        }
    }
    return s[l].k * x + s[l].b;
}

