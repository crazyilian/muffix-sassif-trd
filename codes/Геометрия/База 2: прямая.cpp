struct line {
  dbl a, b, c;

  line() {}
  line(dbl a, dbl b, dbl c) : a(a), b(b), c(c) {}
  line(const vctr A, const vctr B) {
    a = A.y - B.y;
    b = B.x - A.x;
    c = A * B;
    // left halfplane of A->B is positive
    // assert(a != 0 || b != 0);
  }
  void operator*=(dbl x) { a *= x, b *= x, c *= x; }
  void operator/=(dbl x) { a /= x, b /= x, c /= x; }
  dbl get(const vctr P) const { return a * P.x + b * P.y + c; }
  vctr anyPoint() const {
    dbl x = -a * c / (a * a + b * b);
    dbl y = -b * c / (a * a + b * b);
    return {x, y};
  }
  void normalize() {
    dbl d = sqrtl(a * a + b * b);
    a /= d, b /= d, c /= d;
  }
};

bool isparallel(line l1, line l2) {
  return sign(l2.a * l1.b - l2.b * l1.a) == 0;
}

vctr intersection(const line &l1, const line &l2) {
  dbl z = l2.a * l1.b - l2.b * l1.a;
  dbl x = (l1.c * l2.b - l2.c * l1.b) / z;
  dbl y = -(l1.c * l2.a - l2.c * l1.a) / z;
  return {x, y};
}

// Серединный перпендикуляр (не биссектриса!)
line bisection(const vctr A, const vctr B) {
  vctr M = (A + B) / 2;
  return line(M, M + rotate_ccw_90(B - A));
}

