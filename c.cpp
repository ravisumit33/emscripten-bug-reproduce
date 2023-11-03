#include "c.h"
#include <cstdio>

int fun5(int a, int b) { return a + b; }
struct my_struct {
  int x;
  int y;
  bool operator<(const my_struct &other) const { return x < other.x; }
};

int EMSCRIPTEN_KEEPALIVE fun4(int a, int b) {
  printf("%d %d\n", a, b);
  return fun5(a, b);
}
