#include <dlfcn.h>
#include <iostream>

using namespace std;

int main() {
  const char *side_module;
#ifdef __EMSCRIPTEN_PTHREADS__
  side_module = "side_module_mt.wasm";
#else
  side_module = "side_module.wasm";
#endif
  void *side_module_handle = dlopen(side_module, RTLD_LAZY);

  if (!side_module_handle) {
    std::cout << "Error in loading side module: " << dlerror() << std::endl;
    return 1;
  }
  auto fun = (int (*)())(dlsym(side_module_handle, "fun"));
  if (!fun) {
    std::cout << "Error in getting symbol: " << dlerror() << std::endl;
    return 1;
  }
  std::cout << fun() << std::endl;
  return 0;
}
