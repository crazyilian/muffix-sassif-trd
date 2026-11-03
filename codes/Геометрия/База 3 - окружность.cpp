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
    vctr u = B-A, v = D-A;
    dbl p = u.dist2(), q = v.dist2();
    C = A + vctr(v.y*p - u.y*q, u.x*q - v.x*p) / (2*(u*v));
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
  dbl k = sqrtl((c.r - d) * (c.r + d));
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
  dbl k = sqrtl((d - c.r) * (d + c.r));
  // res[0] is right tangent, res[1] is left tangent
  return intersection_circ_circ(circle(v.x, v.y, k), c);
}

// {point on A, point on B}: outer tangents, then inner.
// 4 apart, 3 touch outside, 2 intersect, 1 touch inside,
// 0 nested. Tangent at touching point has equal points 
// (line is perpendicular to A.C->B.C)
vector<pair<vctr, vctr>> common_tangents(circle A, circle B) {
  vctr d = B.C - A.C;
  dbl d2 = d.dist2();
  if (sign(d2) == 0) return {};
  vector<pair<vctr, vctr>> res;
  for (dbl r : {B.r, -B.r}) { // outer, inner
    dbl dr = A.r - r, h2 = d2 - dr * dr;
    if (sign(h2) < 0) continue;
    dbl h = sqrtl(max<dbl>(h2, 0));
    for (int s : {1, -1}) {
      vctr v = (d * dr + d.rotate_ccw_90() * (s * h)) / d2;
      res.pb({A.C + v * A.r, B.C + v * r});
      if (sign(h2) == 0) break;
    }
  }
  return res;
}
