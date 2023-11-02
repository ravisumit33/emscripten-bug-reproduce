#include "b.h"
// #include <cstdio>
#include <emscripten.h>

int fun1(int x) {
  int y = x;
  auto f = [&]() {
    if (y == 1) {
      y = 4;
    } else if (y != 0) {
      y += 1;
    }
  };
  f();
  return y;
}

extern "C" {

int EMSCRIPTEN_KEEPALIVE pmodule(int x) {
  // printf("pmodule\n");
  return fun1(x);
}

int EMSCRIPTEN_KEEPALIVE smodule(int y) { return fun2(y); }
}

int main() { return 0; }
