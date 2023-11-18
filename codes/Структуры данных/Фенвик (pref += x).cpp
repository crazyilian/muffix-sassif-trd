// a[left..right] += delta;  get_sum a[1..pos]
//
//void update(left, right, delta)
//  T1.add(left, delta)
//  T1.add(right + 1, -delta);
//  T2.add(left, delta * (left - 1))
//  T2.add(right + 1, -delta * right);
//
//int getSum(pos)
//  return T1.sum(pos) * pos - T2.sum(pos)

