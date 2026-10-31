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
  bool isin(const vctr P, char strict=0) const {
    // `dist2 - r*r` fails on dbl precision.
    return sign((C - P).dist() - r) <= -strict;
    // return sign((C - P).dist2() - r * r) <= -strict;
  }
};

vector<vctr> intersection_line_circ(line l, circle c) {
  l.normalize();
  dbl s = l.get(c.C), d = abs(s);
  if (sign(d - c.r) > 0) return {};
  vctr a = c.C - vctr(l.a, l.b) * s;
  if (sign(c.r - d) == 0) return {a};
  dbl k = sqrtl(c.r * c.r - d * d);
  vctr v = vctr(l.b, -l.a) * k;
  // arc from res[0] to res[1] ccw lies in positive halfplane
  return {a + v, a - v};
}

vector<vctr> intersection_circ_circ(circle A, circle B) {
  vctr d = B.C - A.C; // better precision
  line l(2*d.x, 2*d.y,
         (B.r-A.r) * (B.r+A.r) - d.dist2());
  if (sign(l.a) == 0 && sign(l.b) == 0) return {};
  auto c = A.r<B.r ? circle(0,0,A.r) : circle(d,B.r); // better precision
  auto res = intersection_line_circ(l, c);
  for (auto &p : res) p += A.C;
  // arc from res[0] to res[1] ccw over A is inside B
  // <=> ccw over B is outside A
  return res;
}

vector<vctr> tangent_vctr_circ(vctr v, circle c) {
  dbl d = (c.C - v).dist();
  if (sign(d - c.r) < 0) return {};
  if (sign(d - c.r) == 0) return {v};
  dbl k = sqrtl(d * d - c.r * c.r);
  // res[0] is right tangent, res[1] is left tangent
  return intersection_circ_circ(circle(v.x, v.y, k), c);
}

