//// Вектор ////

struct vctr {
  dbl x, y;
  vctr() {}
  vctr(dbl x, dbl y) : x(x), y(y) {}

  dbl operator%(const vctr &o) const { return x * o.x + y * o.y; }
  dbl operator*(const vctr &o) const { return x * o.y - y * o.x; }
  vctr operator+(const vctr &o) const { return {x + o.x, y + o.y}; }
  vctr operator-(const vctr &o) const { return {x - o.x, y - o.y}; }
  vctr operator-() const { return {-x, -y}; }
  vctr operator*(const dbl d) const { return {x * d, y * d}; }
  vctr operator/(const dbl d) const { return {x / d, y / d}; }
  void operator+=(const vctr &o) { x += o.x, y += o.y; }
  void operator-=(const vctr &o) { x -= o.x, y -= o.y; }
  dbl dist2() const { return x * x + y * y; }
  dbl dist() const { return sqrtl(dist2()); }
  vctr norm() const { return *this / dist(); }
};

dbl angle_between(const vctr &a, const vctr &b) {
  return atan2(b * a, b % a);
}

// y > 0 ? 0 : 1
bool is2plane(const vctr &a) {
  return sign(a.y) < 0 || (sign(a.y) == 0 && sign(a.x) < 0);
}

bool cmp_angle(const vctr &a, const vctr &b) {
  bool pla = is2plane(a);
  bool plb = is2plane(b);
  if (pla != plb)
    return pla < plb;
  return sign(a * b) > 0;
}

//// Прямая ////

struct line {
  dbl a, b, c;

  line() {}
  line(dbl a, dbl b, dbl c) : a(a), b(b), c(c) {}
  line(const vctr A, const vctr B) {
    a = A.y - B.y;
    b = B.x - A.x;
    c = A * B;
    assert(a != 0 || b != 0);
  }

  void operator*=(dbl x) { a *= x, b *= x, c *= x; }
  void operator/=(dbl x) { a /= x, b /= x, c /= x; }
  dbl get(const vctr P) const { return a * P.x + b * P.y + c; }
  vctr anyPoint() const {
    dbl x = -a * c / (a * a + b * b);
    dbl y = -b * c / (a * a + b * b);
    return vctr(x, y);
  }
  void normalize() {
    dbl d = sqrtl(a * a + b * b);
    a /= d;
    b /= d;
    c /= d;
  }
};

bool isparallel(line l1, line l2) {
  return vctr(l1.a, l1.b) * vctr(l2.a, l2.b) == 0;
}

vctr intersection(const line &l1, const line &l2) {
  dbl x = (l1.c * l2.b - l2.c * l1.b) / (l2.a * l1.b - l2.b * l1.a);
  dbl y = -(l1.c * l2.a - l2.c * l1.a) / (l2.a * l1.b - l2.b * l1.a);
  return vctr(x, y);
}

// Серединный перпендикуляр (не биссектриса!)
line bisection(const vctr A, const vctr B) {
  vctr M = (A + B) / 2;
  vctr AB = B - A;
  vctr norm = vctr(AB.y, -AB.x);
  return line(M, M + norm);
}

//// Окружность ////

struct circle {
  dbl x, y, r;

  circle() {}
  circle(dbl x, dbl y, dbl r) : x(x), y(y), r(r) {}
  circle(vctr P, dbl r) : x(P.x), y(P.y), r(r) {}
  circle(const vctr A, const vctr B) {
    vctr C = (A + B) / 2;
    x = C.x, y = C.y;
    r = (A - B).dist() / 2;
  }
  circle(const vctr A, const vctr B, const vctr C) {
    line l1 = bisection(A, B);
    line l2 = bisection(B, C);
    vctr P = intersection(l1, l2);
    x = P.x, y = P.y;
    r = (P - A).dist();
  }

  bool isin(const vctr P) const {
    return (vctr(x, y) - P).dist2() <= r * r;
  }
  vctr cent() const { return vctr(x, y); }
};


