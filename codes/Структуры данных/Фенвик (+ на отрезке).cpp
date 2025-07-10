// a[l..r) += x
void update(int l, int r, int x) {
  T1.add(l, x);
  T1.add(r, -x);
  T2.add(l, -x * l);
  T2.add(r, x * r);
}

// sum a[0..pos)
int get(int pos) {
  return T1.get(pos) * pos + T2.get(pos);
}

