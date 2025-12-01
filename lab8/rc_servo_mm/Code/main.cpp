#include "DE1.h"
#include <stdio.h>

int main(){
    printf("working... 155\n");
    int OUT_BASE = 0x00000020;
    DE1 my_de1 = DE1();
    my_de1.RegisterWrite(OUT_BASE, 155);
    printf("done\n");
}