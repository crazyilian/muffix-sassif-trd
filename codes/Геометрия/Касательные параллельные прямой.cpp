// find point with max (sgn=1) or min (sgn=-1) signed distance to line
int tangent_parallel_line(const vector<vctr> &p, line l, int sgn) {
  l *= sgn;
  int n = p.size();
  int i = 0;
  int logn = 31 - __builtin_clz(n);
  for (int k = logn; k >= 0; --k) {
    int i1 = (i - (1 << k) + n) % n;
    int i2 = (i + (1 << k)) % n;
    if (l.get(p[i1]) > l.get(p[i])) i = i1;
    if (l.get(p[i2]) > l.get(p[i])) i = i2;
  }
  return i;
}

