#include "c.h"
#include <iostream>
#include <vector>

int EMSCRIPTEN_KEEPALIVE getFibonacci(int n, int p) {
  std::vector<int> dp(n + 1);
  dp[0] = 0;
  dp[1] = 1 % p;
  for (int i = 2; i <= n; ++i) {
    dp[i] = (dp[i - 1] + dp[i - 2]) % p;
  }
  try {
    throw std::runtime_error("Exception from getFibonacci!!!");
  } catch (std::exception &e) {
    std::cout << "Exception caught in getFibonacci" << std::endl;
    throw;
  }
  return dp[n];
}
