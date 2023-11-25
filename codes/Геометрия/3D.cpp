double eps = 1e-7;

struct Pt {
  double x;
  double y;
  double z;

  Pt(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}

  Pt operator-(const Pt& other) const {
    return {x - other.x, y - other.y, z - other.z};
  }

  Pt operator+(const Pt& other) const {
    return {x + other.x, y + other.y, z + other.z};
  }

  Pt operator/(const double& a) const {
    return {x / a, y / a, z / a};
  }

  Pt operator*(const double& a) const {
    return {x * a, y * a, z * a};
  }

  Pt cross(const Pt& p2) const {
    double nx = y * p2.z - z * p2.y;
    double ny = z * p2.x - x * p2.z;
    double nz = x * p2.y - y * p2.x;
    return {nx, ny, nz};
  }

  bool operator==(const Pt& pt) const {
    return abs(x - pt.x) < eps && abs(y - pt.y) < eps && abs(z - pt.z) < eps;
  }

  double dist() {
    return sqrtl(x * x + y * y + z * z);
  }
};

struct Plane {
  double a, b, c, d;

  Plane(double a_, double b_, double c_, double d_) : a(a_), b(b_), c(c_), d(d_) {
    double kek = sqrtl(a * a + b * b + c * c);
    if (kek < eps) return;
    a /= kek;
    b /= kek;
    c /= kek;
    d /= kek;
  }

  double get_val(Pt p) {
    return a * p.x + b * p.y + c * p.z + d;
  }

  bool on_plane(Pt p) {
    return abs(get_val(p)) / sqrtl(a * a + b * b + c * c) < eps;
  }

  Pt proj(Pt p) {
    double t = (a * p.x + b * p.y + c * p.z + d) / (a * a + b * b + c * c);
    return p - Pt(a, b, c) * t;
  }
};

bool on_line(Pt p1, Pt p2, Pt p3) {
  return (p2 - p1).cross(p3 - p1) == Pt(0, 0, 0);
}

Plane get_plane(Pt p1, Pt p2, Pt p3) {
  Pt norm = (p2 - p1).cross(p3 - p1);
  Plane pl(norm.x, norm.y, norm.z, 0);
  pl.d = -pl.get_val(p1);
  return pl;
}

pair<pair<double, double>, pair<double, double>> get_xy(double a, double b, double c) {
  if (abs(a) > eps) {
    double y1 = 0, y2 = 10;
    return {{(-c - b * y1) / a, y1}, {(-c - b * y2) / a, y2}};
  }
  double x1 = 0, x2 = 10;
  return {{x1, (-c - a * x1) / b}, {x2, (-c - a * x2) / b}};
}

pair<Pt, Pt> intersect(Plane pl1, Plane pl2) {
  if (abs(pl2.a) < eps && abs(pl2.b) < eps && abs(pl2.c) < eps) {
    assert(false);
  }
  if (abs(pl2.a) > eps) {
    double nd = pl1.d - pl1.a * pl2.d / pl2.a;
    double nc = pl1.c - pl1.a * pl2.c / pl2.a;
    double nb = pl1.b - pl1.a * pl2.b / pl2.a;
    if (abs(nc) < eps && abs(nb) < eps) {
      // плоскости параллельны (могут совпадать)
      return {Pt(0, 0, 0), Pt(0, 0, 0)};
    }
    auto [yz1, yz2] = get_xy(nb, nc, nd);
    double x1 = (-pl2.d - pl2.c * yz1.second - pl2.b * yz1.first) / pl2.a;
    double x2 = (-pl2.d - pl2.c * yz2.second - pl2.b * yz2.first) / pl2.a;
    return {Pt(x1, yz1.first, yz1.second), Pt(x2, yz2.first, yz2.second)};
  }
  Plane copy_pl1(pl1.c, pl1.a, pl1.b, pl1.d);
  Plane copy_pl2(pl2.c, pl2.a, pl2.b, pl2.d);
  auto [p1, p2] = intersect(copy_pl1, copy_pl2);
  return {Pt(p1.y, p1.z, p1.x), Pt(p2.y, p2.z, p2.x)};
}
