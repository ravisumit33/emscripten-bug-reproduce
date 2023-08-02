#include "b.h"
#include "c.h"

A::A (int x) {
    y = x;
}
int A::fun3(int x) {
    return y*x;
}


int fun2(int a) {
    if (a == 0) {
        return -1;
    } else if (a == 1) {
        return -4;
    }
    A a1(2);
    return fun4(a, a) + a1.fun3(a);
}
