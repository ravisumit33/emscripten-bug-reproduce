#include "b.h"
#include "c.h"
#include <stdexcept>
#include <string>

#ifdef DYN_LINK_RUNTIME
#include "dlfcn.h"
#endif // DYN_LINK_RUNTIME

A::A(int x) { y = x; }
int A::fun3(int x) { return y * x; }

int fun2(int a) {
  if (a == 0) {
    return -1;
  } else if (a == 1) {
    return -4;
  }
  A a1(2);
#ifdef DYN_LINK_RUNTIME
  void *dll_handle = dlopen("x.wasm", RTLD_NOW);
  if (!dll_handle) {
    std::string dlopen_error{"Cannot load library: "};
    dlopen_error += dlerror();
    throw std::runtime_error(dlopen_error);
  }
  decltype(fun4) *_fun4 = (decltype(fun4) *)dlsym(dll_handle, "fun4");
  if (!_fun4) {
    std::string dlsym_error{"Cannot load symbol 'fun4': "};
    dlsym_error += dlerror();
    throw std::runtime_error(dlsym_error);
  }
  return _fun4(a, a) + a1.fun3(a);
#else
  return fun4(a, a) + a1.fun3(a);
#endif // DYN_LINK_RUNTIME
}
