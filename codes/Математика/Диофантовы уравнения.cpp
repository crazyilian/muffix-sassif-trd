pair<int, int> ext_gcd(int a, int b) {
  int x1 = 1, y1 = 0, x2 = 0, y2 = 1;
  while (b) {
    int k = a / b;
    x1 = x1 - x2 * k;
    y1 = y1 - y2 * k;
    swap(x1, x2);
    swap(y1, y2);
    a %= b;
    swap(a, b);
  }
  return {x1, y1};
}

bool cool_ext_gcd(int a, int b, int c, int &x, int &y) {
  if (b == 0) {
    y = 0;
    if (a == 0) {
      x = 0;
      return c == 0;
    } else {
      x = c / a;
      return c % a == 0;
    }
  }
  auto [x0, y0] = ext_gcd(a, b);
  int g = x0 * a + y0 * b;
  if (c % g != 0)
    return false;
  x0 *= c / g;
  y0 *= c / g;
  int t = b / g;
  int k = (-x0) / t;
  if (x0 + t * k < 0)
    k += t / abs(t);
  x = x0 + t * k;
  y = y0 - (a / g) * k;
  return true;
}
