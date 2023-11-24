// a[l..r) += x
void update(int l, int r, int x) {
  T1.add(l, x);
  T1.add(r, -x);
  T2.add(l, -x * l);
  T2.add(r, x * r);
}

// sum a[0..pos)
int rsq(int pos) {
  return T1.rsq(pos) * pos + T2.rsq(pos);
}

// sum a[l..r)
int sum(int l, int r) {
  return rsq(r) - rsq(l);
}

