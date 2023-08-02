#include <cstdio>
#include "b.h"
#include <emscripten.h>

int fun1(int x){
    printf("fun1\n");
    if (x == 0) {
        return 0;
    } else if (x == 1) {
        return 4;
    }
    return x + 1;
}

extern "C" {
    
int EMSCRIPTEN_KEEPALIVE pmodule(int x) {
    printf("pmodule\n");
    return fun1(x);
}

int EMSCRIPTEN_KEEPALIVE smodule(int y) {
    // std::cout << "smodule" << std::endl;
    return fun2(y);
}
}

int main()
{
    return 0;
}
