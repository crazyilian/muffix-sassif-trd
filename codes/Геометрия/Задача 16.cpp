bool is_in_same_half(vctr p, vctr r1, vctr r2) {
  return sign((r2 - r1) % (p - r1)) >= 0;
}

dbl dist_point_point(vctr a, vctr b) { return (a-b).dist(); }

dbl dist_point_line(vctr a, vctr l1, vctr l2) {
  return abs((l2 - l1) * (a - l1)) / (l2 - l1).dist();
}

dbl dist_point_ray(vctr a, vctr r1, vctr r2) {
  if (r1 == r2 || !is_in_same_half(a, r1, r2))
    return dist_point_point(a, r1);
  return dist_point_line(a, r1, r2);
}

dbl dist_point_seg(vctr a, vctr s1, vctr s2) {
  return max(dist_point_ray(a, s1, s2),
             dist_point_ray(a, s2, s1));
}

dbl dist_line_line(vctr l1a, vctr l1b, vctr l2a, vctr l2b) {
  if (sign((l1b - l1a) * (l2b - l2a))) return 0;
  return dist_point_line(l1a, l2a, l2b);
}

dbl dist_ray_line(vctr r1, vctr r2, vctr l1, vctr l2) {
  vctr d = l2 - l1;
  if (sign(d * (r1 - l1)) * sign(d * (r2 - r1)) < 0) return 0;
  return dist_point_line(r1, l1, l2);
}

dbl dist_seg_line(vctr s1, vctr s2, vctr l1, vctr l2) {
  return max(dist_ray_line(s1, s2, l1, l2),
             dist_ray_line(s2, s1, l1, l2));
}

dbl dist_ray_ray(vctr r1a, vctr r1b, vctr r2a, vctr r2b) {
  vctr u = r1b - r1a, v = r2b - r2a, w = r2a - r1a;
  int c = sign(u * v); // cross not at the ray starts:
  if (sign(w * v) * c > 0 && sign(w * u) * c > 0) return 0;
  return min(dist_point_ray(r1a, r2a, r2b),
             dist_point_ray(r2a, r1a, r1b));
}

dbl dist_seg_ray(vctr s1, vctr s2, vctr r1, vctr r2) {
  return max(dist_ray_ray(s1, s2, r1, r2),
             dist_ray_ray(s2, s1, r1, r2));
}

dbl dist_seg_seg(vctr s1a, vctr s1b, vctr s2a, vctr s2b) {
  return max(dist_seg_ray(s1a, s1b, s2a, s2b),
             dist_seg_ray(s1a, s1b, s2b, s2a));
}
