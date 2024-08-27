#include "b.h"
// #include <cstdio>
#include <emscripten.h>
#include <thread>

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

int main() {

#ifdef __EMSCRIPTEN_PTHREADS__
  std::thread t(smodule, 2);
  t.join();
#else
  smodule(2);
#endif
  return 0;
}
