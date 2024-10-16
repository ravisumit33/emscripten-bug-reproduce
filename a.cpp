#include "b.h"
#include <ctime>
#include <emscripten.h>
#include <iostream>
#include <thread>

int fun1(int x) {
  try {
    throw std::runtime_error("Exception from getFibonacci!!!");
  } catch (std::exception &e) {
    throw;
  }
}

extern "C" {

int EMSCRIPTEN_KEEPALIVE pmodule(int x) {
  // printf("pmodule\n");
  const clock_t begin_time = clock();
  static int count = 0;
  std::cout << "#" << count++ << std::endl;
  int ret = -1;
  for (int i = 0; i < 1; ++i) {
    try {
      if (i % 100000 == 0) {
        std::cout << "Calling fun1 from pmodule " << i << "th time"
                  << std::endl;
      }
      ret = fun1(x);
    } catch (...) {
      if (i % 100000 == 0) {
        std::cout << "Exception caught in pmodule" << std::endl;
      }
    }
  }
  std::cout << "Time taken by pmodule: "
            << float(clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
  std::cout << "Response from pmodule: " << ret << std::endl;
  return ret;
}

int EMSCRIPTEN_KEEPALIVE smodule(int y, int mod) {
  const clock_t begin_time = clock();
  static int count = 0;
  std::cout << "#" << count++ << ": " << mod << std::endl;
  int ret = -1;
  for (int i = 0; i < 1; ++i) {
    try {
      if (i % 100000 == 0) {
        std::cout << "Calling fun2 from smodule " << i << "th time"
                  << std::endl;
      }
      ret = fun2(y, mod);
    } catch (...) {
      if (i % 100000 == 0) {
        std::cout << "Exception caught in smodule" << std::endl;
      }
    }
  }
  std::cout << "Time taken by smodule: "
            << float(clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
  std::cout << "Response from smodule: " << ret << std::endl;
  return ret;
}
}

int main() {

  std::cout << "Hello from main" << std::endl;
  return 0;
  const clock_t begin_time = clock();
#ifdef __EMSCRIPTEN_PTHREADS__
  std::thread t(smodule, 3e7, 17);
  t.join();
#else
  smodule(3e7, 17);
#endif
  std::cout << "Time taken to complete computation : "
            << float(clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
  return 0;
}
