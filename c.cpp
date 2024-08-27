#include "c.h"
#include <cstdio>

int fun5(int a, int b) { return a + b; }

int EMSCRIPTEN_KEEPALIVE fun4(int a, int b) {
  printf("%d %d\n", a, b);
  return fun5(a, b);
}
