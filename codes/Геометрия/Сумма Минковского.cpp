// Список вершин -> список рёбер
vector<vctr> poly_to_edges(const vector<vctr> &A) {
  vector<vctr> edg(A.size());
  for (int i = 0; i < A.size(); ++i)
    edg[i] = A[(i + 1) % A.size()] - A[i];
  return edg;
}

// A и B начинаются с минимальных вершин
vector<vctr> minkowski_sum(const vector<vctr> &A, const vector<vctr> &B) {
  auto edgA = poly_to_edges(A);
  auto edgB = poly_to_edges(B);
  vector<vctr> edgC(A.size() + B.size());
  merge(edgA.begin(), edgA.end(), edgB.begin(), edgB.end(), edgC.begin(), cmp_angle);
  vector<vctr> C(edgC.size());
  C[0] = A[0] + B[0];
  for (int i = 0; i + 1 < C.size(); ++i)
    C[i + 1] = C[i] + edgC[i];
  return C;
}

