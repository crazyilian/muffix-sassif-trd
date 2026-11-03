// closed segments AB and CD (can be points)
bool is_intersection_seg(vctr A, vctr B, vctr C, vctr D) {
  auto box = [](auto a, auto b, auto c, auto d) {
    return max(min(a,b), min(c,d)) <= min(max(a,b), max(c,d));
  };
  return box(A.x, B.x, C.x, D.x) && box(A.y, B.y, C.y, D.y)
    && sign((B-A) * (C-A)) * sign((B-A) * (D-A)) <= 0
    && sign((D-C) * (A-C)) * sign((D-C) * (B-C)) <= 0;
}
