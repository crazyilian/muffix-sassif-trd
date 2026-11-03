char sign(dbl x) { return (x > EPS) - (x < -EPS); }
struct vctr {
  dbl x, y;
  vctr() {}
  vctr(dbl x, dbl y) : x(x), y(y) {}
  dbl operator%(const vctr &o)const{return x*o.x+y*o.y;}
  dbl operator*(const vctr &o)const{return x*o.y-y*o.x;}
  vctr operator+(const vctr &o)const{return{x+o.x,y+o.y};}
  vctr operator-(const vctr &o)const{return{x-o.x,y-o.y};}
  vctr operator-() const { return {-x, -y}; }
  vctr operator*(const dbl d)const{return{x*d,y*d};}
  vctr operator/(const dbl d)const{return{x/d,y/d};}
  void operator+=(const vctr &o) { x += o.x, y += o.y; }
  void operator-=(const vctr &o) { x -= o.x, y -= o.y; }
  bool operator==(const vctr &o)const{ return !sign(x-o.x) && !sign(y-o.y); }
  dbl dist2() const { return x * x + y * y; }
  dbl dist() const { return sqrtl(dist2()); }
  vctr norm() const { return *this / dist(); }
  vctr rotate_ccw_90() const {  return {-y, x}; }
};

// противоположные (a*b == 0): +pi или -pi, знак от шума
dbl angle_between(const vctr &a, const vctr &b) {
  return atan2(a*b, a%b); // ccw от a до b, знак совпадает с a*b
}

const dbl PI = acosl(-1);
// ccw от a до b в [0, 2pi), ~2pi -> 0
dbl angle_between_positive(const vctr &a, const vctr &b) {
  dbl r = atan2(a*b, a%b);
  if (r < 0) r += 2 * PI;
  return r > 2 * PI - EPS ? 0 : r;
}

// y > 0 ? 0 : 1
bool is2plane(const vctr &a) {
  return sign(a.y)<0 || (sign(a.y)==0 && sign(a.x)<0);
}

bool cmp_angle(const vctr &a, const vctr &b) {
  bool pla = is2plane(a);
  bool plb = is2plane(b);
  if (pla != plb) return pla < plb;
  return sign(a * b) > 0;
}

vctr rotate_ccw(const vctr &a, dbl phi) {
  dbl cs = cosl(phi);
  dbl sn = sinl(phi);
  return {a.x * cs - a.y * sn, a.y * cs + a.x * sn};
}

