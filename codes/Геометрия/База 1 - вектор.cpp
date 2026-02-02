char sign(dbl x) { return x < -EPS ? -1 : x > EPS; }
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
  dbl dist2() const { return x * x + y * y; }
  dbl dist() const { return sqrtl(dist2()); }
  vctr norm() const { return *this / dist(); }
  vctr rotate_ccw_90() const {  return {-y, x}; }
};

dbl angle_between(const vctr &a, const vctr &b) {
  return atan2(b * a, b % a);
}

// y > 0 ? 0 : 1
bool is2plane(const vctr &a) {
  return sign(a.y)<0 || (sign(a.y)==0 && sign(a.x)<0);
}

bool cmp_angle(const vctr &a, const vctr &b) {
  bool pla = is2plane(a);
  bool plb = is2plane(b);
  if (pla != plb)
    return pla < plb;
  return sign(a * b) > 0;
}

vctr rotate_ccw(const vctr &a, dbl phi) {
  dbl cs = cos(phi);
  dbl sn = sin(phi);
  return {a.x * cs - a.y * sn, a.y * cs + a.x * sn};
}

