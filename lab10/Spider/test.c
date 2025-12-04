#include <stdio.h>

int main(){
    char msg[] = "waiting for char c >> ";
    printf('%s'. msg);
    while (getchar() != 'c') {
        printf('%s'. msg);
    }
}