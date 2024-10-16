#include "b.h"
#include "c.h"
#include <stdexcept>
#include <string>

#ifdef DYN_LINK_RUNTIME
#include "dlfcn.h"
#endif // DYN_LINK_RUNTIME

int fun2(int a, int mod) {
#ifdef DYN_LINK_RUNTIME
  void *dll_handle = dlopen("x.wasm", RTLD_NOW);
  if (!dll_handle) {
    std::string dlopen_error{"Cannot load library: "};
    dlopen_error += dlerror();
    throw std::runtime_error(dlopen_error);
  }
  decltype(getFibonacci) *_getFibonacci =
      (decltype(getFibonacci) *)dlsym(dll_handle, "getFibonacci");
  if (!_getFibonacci) {
    std::string dlsym_error{"Cannot load symbol 'getFibonacci': "};
    dlsym_error += dlerror();
    throw std::runtime_error(dlsym_error);
  }
  return _getFibonacci(a, mod);
#else
  return getFibonacci(a, mod);
#endif // DYN_LINK_RUNTIME
}
