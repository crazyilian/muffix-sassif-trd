struct Pt {
  double x, y, z;

  Pt cross(const Pt& p2) const {
    double nx = y * p2.z - z * p2.y;
    double ny = z * p2.x - x * p2.z;
    double nz = x * p2.y - y * p2.x;
    return {nx, ny, nz};
  }
};

struct Plane {
  double a, b, c, d;
  
  double get_val(Pt p) {
    return a * p.x + b * p.y + c * p.z + d;
  }
};

Plane get_plane(Pt p1, Pt p2, Pt p3) {
  Pt norm = (p2 - p1).cross(p3 - p1);
  Plane pl(norm.x, norm.y, norm.z, 0);
  pl.d = -pl.get_val(p1);
  return pl;
}
