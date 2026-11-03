// A, B: CCW from min (y, x), no 3 collinear, size >= 1.
// Result: CCW from min, no points on sides, no duplicates
vector<vctr> minkowski_sum(vector<vctr> A, vector<vctr> B) {
  int n = A.size(), m = B.size();
  A.pb(A[0]), A.pb(A[1 % n]);
  B.pb(B[0]), B.pb(B[1 % m]);
  vector<vctr> C; C.reserve(n+m);
  for (int i = 0, j = 0; i < n || j < m; ) {
    C.pb(A[i] + B[j]);
    vctr a = A[i + 1] - A[i], b = B[j + 1] - B[j];
    // cmp_angle from vctr template
    int c = j==m ? 1 : i==n || cmp_angle(b,a) ? -1 : cmp_angle(a,b);
    if (c >= 0) ++i;
    if (c <= 0) ++j;
  }
  return C;
}
