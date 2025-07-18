// a[l..r) += x
void update(int l, int r, int x) {
  T1.add(l, x);
  T1.add(r, -x);
  T2.add(l, -x * l);
  T2.add(r, x * r);
}

// sum a[0..i)
int get(int i) {
  return T1.get(i) * i + T2.get(i);
}

