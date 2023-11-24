vctr minvctr(INF, INF);

bool cmp_convex_hull(const vctr &a, const vctr &b) {
  vctr A = a - minvctr;
  vctr B = b - minvctr;
  auto sign_prod = sign(A * B);
  if (sign_prod != 0)
    return sign_prod > 0;
  return A.dist2() < B.dist2();
}

// minvctr updates here
vector<vctr> get_convex_hull(vector<vctr> arr) {
  minvctr = rotate_min_vctr(arr);
  vector<vctr> hull;
  sort(arr.begin(), arr.end(), cmp_convex_hull);
  for (vctr &el : arr) {
    while (hull.size() > 1 && sign((hull.back() - hull[hull.size() - 2]) * (el - hull.back())) <= 0)
      hull.pop_back();
    hull.push_back(el);
  }
  return hull;
}

