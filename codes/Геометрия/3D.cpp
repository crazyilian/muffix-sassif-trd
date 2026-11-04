struct Pt {
  dbl x, y, z;
  Pt() : x(0), y(0), z(0) {}
  Pt(dbl x, dbl y, dbl z) : x(x), y(y), z(z) {}
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

// две точки прямой пересечения на расстоянии 1
pair<Pt, Pt> intersect(Plane pl1, Plane pl2) {
  Pt n1(pl1.a, pl1.b, pl1.c), n2(pl2.a, pl2.b, pl2.c);
  Pt dir = n1.cross(n2);
  dbl len2 = dir.dot(dir);
  if (len2 < EPS * EPS) return {Pt(), Pt()}; // параллельны
  Pt p = (n1 * pl2.d - n2 * pl1.d).cross(dir) / len2;
  return {p, p + dir / sqrtl(len2)};
}

// угол между векторами в [0, pi]: сонаправленные -> 0, противоположные -> pi
// угол между прямыми с направляющими p1, p2: min(a, pi - a)
dbl get_ang(Pt p1, Pt p2) {
  return atan2l(p1.cross(p2).dist(), p1.dot(p2));
}

// любой перпендикулярный вектор
Pt vector_perp(Pt v) {
  if (abs(v.x) > EPS || abs(v.y) > EPS)
    return {v.y, -v.x, 0};
  return {v.z, 0, -v.x};
}

// плоскость через точку p перпендикулярная вектору v
Plane plane_perp(Pt p, Pt v) {
  return Plane(v.x, v.y, v.z, -v.dot(p));
}

// ближайшая к p точка прямой ab; при |a-b| < EPS ответ a
Pt closest_line(Pt p, Pt a, Pt b) {
  Pt v = b - a;
  dbl len2 = v.dot(v);
  if (len2 < EPS * EPS) return a;
  return a + v * ((p - a).dot(v) / len2);
}

// ближайшая к p точка луча из a в сторону b
Pt closest_ray(Pt p, Pt a, Pt b) {
  if ((p - a).dot(b - a) < EPS) return a;
  return closest_line(p, a, b);
}

// ближайшая к p точка отрезка ab
Pt closest_seg(Pt p, Pt a, Pt b) {
  if ((p - b).dot(a - b) < EPS) return b;
  return closest_ray(p, a, b);
}

// прямая a + (b - a) * t; |b-a| и длина нормали > EPS
// 0 -- нет, 1 -- точка, 2 -- прямая лежит в плоскости
// t записывается при ответе 1
// луч: t >= 0; отрезок: 0 <= t <= 1
int intersect(Pt a, Pt b, Plane pl, dbl &t) {
  Pt v = b - a, n(pl.a, pl.b, pl.c);
  dbl len = n.dist(), den = n.dot(v), val = pl.get_val(a);
  assert(len > EPS && v.dot(v) > EPS * EPS);
  if (abs(den) < EPS * max<dbl>(1, len * v.dist()))
    return abs(val) < EPS * len ? 2 : 0;
  t = -val / den;
  return 1;
}

// ортонормированный базис плоскости через o; |n| > EPS
struct Basis {
  Pt o, u, v;
  Basis(Pt o, Pt n) : o(o) {
    dbl len = n.dist();
    assert(len > EPS);
    n = n / len;
    u = vector_perp(n);
    u = u / u.dist();
    v = n.cross(u);
  }
  // для точки вне плоскости -- координаты её проекции
  pair<dbl, dbl> to_2d(Pt p) const {
    p = p - o;
    return {p.dot(u), p.dot(v)};
  }
  Pt from_2d(dbl x, dbl y) const {
    return o + u * x + v * y;
  }
};
