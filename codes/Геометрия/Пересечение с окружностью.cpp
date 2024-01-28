bool is_intersection_line_circ(line l, circle c) {
  l.normalize();
  dbl d = abs(l.get(c.cent()));
  return d < c.r - EPS;
}

vector<vctr> intersection_line_circ(line l, circle c) {
  l.normalize();
  dbl d = abs(l.get(c.cent()));
  vctr per = vctr(l.a, l.b).norm() * d;
  vctr a = c.cent() + per;
  if (sign(d - c.r) > 0)
      return {};
  if (sign(l.get(a)) != 0)
      a = c.cent() - per;
  if (sign(c.r - d) == 0)
    return {a};
  dbl k = sqrtl(c.r * c.r - d * d);
  vctr par = vctr(-l.b, l.a).norm() * k;
  return {a + par, a - par};
}

vector<vctr> intersection_circ_circ(circle a, circle b) {
  line l(2 * (b.x - a.x),
         2 * (b.y - a.y),
         b.r * b.r - a.r * a.r
             + (a.x * a.x + a.y * a.y)
             - (b.x * b.x + b.y * b.y));
  if (sign(l.a) == 0 && sign(l.b) == 0)
    return {};
  return intersection_line_circ(l, a);
}

vector<vctr> tangent_vctr_circ(vctr v, circle c) {
  dbl d = (c.cent() - v).dist();
  dbl k = sqrtl(d * d - c.r * c.r);
  circle c2(v.x, v.y, k);
  return intersection_circ_circ(c, c2);
}

