// Выпуклый многоугольник, P[0] = minvctr
bool is_point_in_poly(vctr A, vector<vctr> &P) {
  auto tmp = A - P[0];
  if (sign(tmp.y) < 0 || (sign(tmp.y) == 0 && sign(tmp.x) < 0))
    return false;
  if (sign(tmp.y) == 0 && sign(tmp.x) == 0)
    return true;
  int ind = lower_bound(P.begin(), P.end(), A, cmp_convex_hull) - P.begin();
  assert(ind != 0);
  if (ind == P.size())
    return false;
  vctr B = A - P[ind - 1];
  vctr C = P[ind] - P[ind - 1];
  return sign(C * B) >= 0;
}

bool is_point_in_poly_strict(vctr A, vector<vctr> &P) {
  if (sign(A.y - P[0].y) <= 0 || sign((A - P[0]) * (P.back() - P[0])) <= 0)
      return false;
  int ind = lower_bound(P.begin(), P.end(), A, cmp_convex_hull) - P.begin();
  assert(ind != 0 && ind != P.size());
  vctr B = A - P[ind - 1];
  vctr C = P[ind] - P[ind - 1];
  return sign(C * B) > 0;
}

