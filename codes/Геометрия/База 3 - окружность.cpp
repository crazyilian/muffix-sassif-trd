struct circle {
  vctr C;
  dbl r;

  circle() {}
  circle(dbl x, dbl y, dbl r) : C(x, y), r(r) {}
  circle(vctr C, dbl r) : C(C), r(r) {}
  circle(const vctr A, const vctr B) {
    C = (A + B) / 2;
    r = (A - B).dist() / 2;
  }
  circle(const vctr A, const vctr B, const vctr D) {
    line l1 = bisection(A, B);
    line l2 = bisection(B, D);
    C = intersection(l1, l2);
    r = (C - A).dist();
  }

  bool isin(const vctr P) const {
    return sign((C - P).dist2() - r * r) <= 0;
  }
};

vector<vctr> intersection_line_circ(line l, circle c) {
  l.normalize();
  dbl d = abs(l.get(c.C));
  vctr per = vctr(l.a, l.b).norm() * d;
  vctr a = c.C + per;
  if (sign(d - c.r) > 0)
    return {};
  if (sign(l.get(a)) != 0)
    a = c.C - per;
  if (sign(c.r - d) == 0)
    return {a};
  dbl k = sqrtl(c.r * c.r - d * d);
  vctr v = vctr(-l.b, l.a).norm() * k;
  return {a + v, a - v};
}

vector<vctr> intersection_circ_circ(circle A, circle B) {
  vctr a = A.C, b = B.C;
  line l(2 * (b.x - a.x),
         2 * (b.y - a.y),
         B.r * B.r - A.r * A.r
             + (a.x * a.x + a.y * a.y)
             - (b.x * b.x + b.y * b.y));
  if (sign(l.a) == 0 && sign(l.b) == 0)
    return {};
  return intersection_line_circ(l, A);
}

vector<vctr> tangent_vctr_circ(vctr v, circle c) {
  dbl d = (c.C - v).dist();
  dbl k = sqrtl(d * d - c.r * c.r);
  circle c2(v.x, v.y, k);
  return intersection_circ_circ(c, c2);
}

