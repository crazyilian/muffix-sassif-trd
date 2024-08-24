// Выпуклый многоугольник, P[0] = minvctr
bool is_point_in_poly(vctr A, vector<vctr> &P) {
  int n = P.size();
  int ind = lower_bound(P.begin(), P.end(), A, cmp_convex_hull) - P.begin();
  if (ind == n || ind == 0)
    return false;
  if (ind == 0)
    ind++;
  vctr B = A - P[ind - 1];
  vctr C = P[ind] - P[ind - 1];
  return sign(C * B) >= 0;
}

