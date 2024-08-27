int alphabeta(int player, int alpha, int beta, int depth) {
  if (depth == 0) {
    // return current position score
  }
  if (player == 0) { // maximization player
    int val = -INF;
    for (auto move : possible_moves) {
      val = max(val, alphabeta(1, alpha, beta, depth - 1));
      if (val > beta) break;
      alpha = max(alpha, val);
    }
    return val;
  } else {
    int val = INF;
    for (auto move : possible_moves) {
      val = min(val, alphabeta(0, alpha, beta, depth - 1));
      if (val < alpha) break;
      beta = min(beta, val);
    }
    return val;
  }
}
