#include <iostream>

int my_create() {
  printf("Inside my create\n");
  return 6;
}

auto fun_ptr = my_create;

extern "C" {
int fun() {
  printf("Inside fun\n");
  return fun_ptr();
}
}
