bool isInSameHalf(vctr p, vctr r1, vctr r2) {
  return sign((r2 - r1) % (p - r1)) >= 0;
}

dbl distPointPoint(vctr a, vctr b) {
  return (a - b).dist();
}

dbl distPointLine(vctr a, vctr l1, vctr l2) {
  return abs((l2 - l1) * (a - l1)) / (l2 - l1).dist();
}

dbl distPointRay(vctr a, vctr r1, vctr r2) {
  if (r1 == r2 || !isInSameHalf(a, r1, r2))
    return distPointPoint(a, r1);
  return distPointLine(a, r1, r2);
}

dbl distPointSeg(vctr a, vctr s1, vctr s2) {
  return max(distPointRay(a, s1, s2),
             distPointRay(a, s2, s1));
}

dbl distLineLine(vctr l1a, vctr l1b, vctr l2a, vctr l2b) {
  if (sign((l1b - l1a) * (l2b - l2a))) return 0;
  return distPointLine(l1a, l2a, l2b);
}

dbl distRayLine(vctr r1, vctr r2, vctr l1, vctr l2) {
  vctr d = l2 - l1;
  if (sign(d * (r1 - l1)) * sign(d * (r2 - r1)) < 0) return 0;
  return distPointLine(r1, l1, l2);
}

dbl distSegLine(vctr s1, vctr s2, vctr l1, vctr l2) {
  return max(distRayLine(s1, s2, l1, l2),
             distRayLine(s2, s1, l1, l2));
}

dbl distRayRay(vctr r1a, vctr r1b, vctr r2a, vctr r2b) {
  vctr u = r1b - r1a, v = r2b - r2a, w = r2a - r1a;
  int c = sign(u * v); // cross not at the ray starts:
  if (sign(w * v) * c > 0 && sign(w * u) * c > 0) return 0;
  return min(distPointRay(r1a, r2a, r2b),
             distPointRay(r2a, r1a, r1b));
}

dbl distSegRay(vctr s1, vctr s2, vctr r1, vctr r2) {
  return max(distRayRay(s1, s2, r1, r2),
             distRayRay(s2, s1, r1, r2));
}

dbl distSegSeg(vctr s1a, vctr s1b, vctr s2a, vctr s2b) {
  return max(distSegRay(s1a, s1b, s2a, s2b),
             distSegRay(s1a, s1b, s2b, s2a));
}
