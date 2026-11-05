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
  dbl get(const vctr P) const { return a*P.x + b*P.y + c; }
  // requires dbl vctr
  vctr any_point() const {
    dbl d = a * a + b * b;
    return {-a * c / d, -b * c / d};
  }
  // requires dbl line
  void normalize() {
    dbl d = sqrtl(a * a + b * b);
    a /= d, b /= d, c /= d;
  }
};

bool isparallel(line l1, line l2) {
  return sign(l2.a * l1.b - l2.b * l1.a) == 0;
}

// requires dbl vctr
vctr intersection(const line &l1, const line &l2) {
  dbl z = l2.a * l1.b - l2.b * l1.a;
  dbl x = (l1.c * l2.b - l2.c * l1.b) / z;
  dbl y = -(l1.c * l2.a - l2.c * l1.a) / z;
  return {x, y};
}

// Серединный перпендикуляр (не биссектриса!), get(A) > 0
line bisection(const vctr A, const vctr B) {
  vctr d = (A - B) * 2;
  return line(d.x, d.y, B.dist2() - A.dist2());
}
