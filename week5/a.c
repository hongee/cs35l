#include "stdio.h"

int someloop(int in) {
    for(int i=0; i < in; i++) {
        printf("Boo");
    }
    return in * in;
}

int main() {
    someloop(5);
}
