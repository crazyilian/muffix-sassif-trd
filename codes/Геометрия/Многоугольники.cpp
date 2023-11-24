// Сдвиг многоугольника, чтобы начинался с минимального вектора
vctr rotate_min_vctr(vector<vctr> &pts) {
  int ind = 0;
  for (int i = 1; i < pts.size(); ++i) {
    if (is2plane(pts[i] - pts[ind]))
      ind = i;
  }
  rotate(pts.begin(), pts.begin() + ind, pts.end());
  return pts[0];
}

// Список вершин -> список рёбер
vector<vctr> poly_to_edges(const vector<vctr> &A) {
  vector<vctr> edg(A.size());
  for (int i = 0; i < A.size(); ++i)
    edg[i] = A[(i + 1) % A.size()] - A[i];
  return edg;
}

