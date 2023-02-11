#include <iostream>

static int my_create();

struct my_struct {
  int (*create)();
};

static const my_struct mstrct = {my_create};

static int my_create() {
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
