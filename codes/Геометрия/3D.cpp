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

  Plane(double a_, double b_, double c_, double d_) : a(a_), b(b_), c(c_), d(d_) {}

  double get_val(Pt p) {
    return a * p.x + b * p.y + c * p.z + d;
  }

  bool on_plane(Pt p) {
    return abs(get_val(p)) / hypot(a, b, c) < eps;
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
