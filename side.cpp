#include <iostream>

int my_create();

struct my_struct {
  int (*create)();
};

const my_struct mstrct = {my_create};

int my_create() {
  printf("Inside my create\n");
  return 6;
}

extern "C" {
int fun() {
  printf("Inside fun\n");
  const my_struct *ptr = &mstrct;
  return ptr->create();
}
}
