const double lambda = 0.999;
double temperature = 1;
mt19937 rnd(777);

double gen_rand_01() {
  return rnd() / (double) UINT32_MAX;
}
bool f(int delta) {
  return exp(-delta / temperature) > gen_rand_01();
}
void make_change() {
  temperature *= lambda;
  // calc change score
  if (change_score <= 0 || f(change_score)) {
    score += change_score;
    // make change
  }
}
