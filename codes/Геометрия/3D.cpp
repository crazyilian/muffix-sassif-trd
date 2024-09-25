struct Pt {
  dbl x, y, z;

  Pt() : x(0), y(0), z(0) {}
  Pt(dbl x_, dbl y_, dbl z_) : x(x_), y(y_), z(z_) {}

  Pt operator-(const Pt& o) const {
    return {x - o.x, y - o.y, z - o.z};
  }
  Pt operator+(const Pt& o) const {
    return {x + o.x, y + o.y, z + o.z};
  }
  Pt operator/(const dbl& a) const {
    return {x / a, y / a, z / a};
  }
  Pt operator*(const dbl& a) const {
    return {x * a, y * a, z * a};
  }
  Pt cross(const Pt& o) const {
    dbl nx = y * o.z - z * o.y;
    dbl ny = z * o.x - x * o.z;
    dbl nz = x * o.y - y * o.x;
    return {nx, ny, nz};
  }
  dbl dot(const Pt &o) const {
    return x * o.x + y * o.y + z * o.z;
  }
  bool operator==(const Pt& o) const {
    return abs(x - o.x) < EPS && abs(y - o.y) < EPS && abs(z - o.z) < EPS;
  }
  dbl dist() {
    return sqrtl(x * x + y * y + z * z);
  }
};

struct Plane {
  dbl a, b, c, d;

  Plane(dbl a_, dbl b_, dbl c_, dbl d_) : a(a_), b(b_), c(c_), d(d_) {
    dbl z = sqrtl(a * a + b * b + c * c);
    if (z < EPS) return;
    a /= z, b /= z, c /= z, d /= z;
  }
  dbl get_val(const Pt &p) const {
    // НЕ СТАВИТЬ МОДУЛЬ
    return a * p.x + b * p.y + c * p.z + d;
  }
  dbl dist(const Pt &p) const {
    return abs(get_val(p));
  }
  bool on_plane(const Pt &p) const {
    return dist(p) / sqrtl(a * a + b * b + c * c) < EPS;
  }
  Pt proj(const Pt &p) const {
    dbl t = get_val(p) / (a * a + b * b + c * c);
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

pair<pair<dbl, dbl>, pair<dbl, dbl>> get_xy(dbl a, dbl b, dbl c) {
  if (abs(a) > EPS) {
    dbl y1 = 0, y2 = 10;
    return {{(-c - b * y1) / a, y1}, {(-c - b * y2) / a, y2}};
  }
  dbl x1 = 0, x2 = 10;
  return {{x1, (-c - a * x1) / b}, {x2, (-c - a * x2) / b}};
}

pair<Pt, Pt> intersect(Plane pl1, Plane pl2) {
  if (abs(pl2.a) < EPS && abs(pl2.b) < EPS && abs(pl2.c) < EPS) {
    assert(false);
  }
  if (abs(pl2.a) > EPS) {
    dbl nd = pl1.d - pl1.a * pl2.d / pl2.a;
    dbl nc = pl1.c - pl1.a * pl2.c / pl2.a;
    dbl nb = pl1.b - pl1.a * pl2.b / pl2.a;
    if (abs(nc) < EPS && abs(nb) < EPS) {
      // плоскости параллельны (могут совпадать)
      return {Pt(0, 0, 0), Pt(0, 0, 0)};
    }
    auto [yz1, yz2] = get_xy(nb, nc, nd);
    dbl x1 = (-pl2.d - pl2.c * yz1.second - pl2.b * yz1.first) / pl2.a;
    dbl x2 = (-pl2.d - pl2.c * yz2.second - pl2.b * yz2.first) / pl2.a;
    return {Pt(x1, yz1.first, yz1.second), Pt(x2, yz2.first, yz2.second)};
  }
  Plane copy_pl1(pl1.c, pl1.a, pl1.b, pl1.d);
  Plane copy_pl2(pl2.c, pl2.a, pl2.b, pl2.d);
  auto [p1, p2] = intersect(copy_pl1, copy_pl2);
  return {Pt(p1.y, p1.z, p1.x), Pt(p2.y, p2.z, p2.x)};
}

// угол между двумя векторами
dbl get_ang(Pt p1, Pt p2) {
  return acosl(p1.dot(p2) / p1.dist() / p2.dist());
}

// любой перпендикулярный вектор
Pt vector_perp(Pt v1) {
  if (abs(v1.x) > EPS || abs(v1.y) > EPS)
    return {v1.y, -v1.x, 0};
  return {v1.z, 0, -v1.x};
}

// плоскость через точку p перпендикулярная вектору v
Plane plane_perp(Pt p, Pt v) {
  Pt v1 = vector_perp(v);
  Pt v2 = v.cross(v1);
  return get_plane(p, v1 + p, v2 + p);
}
