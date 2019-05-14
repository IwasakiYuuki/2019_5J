#include <stdio.h>

int getMax_1(int a, int b);
int getMax_2(int a, int b);
int getMax_3(int a, int b);

int main(){
    printf("1. %d\n", getMax_1(1, 5));
    printf("2. %d\n", getMax_2(1, 5));
    printf("3. %d\n", getMax_3(1, 5));

    return 0;
}

int getMax_1(int a, int b){
    int max;
    if (a >= b) max = a;
    else max = b;
    return max;
}

int getMax_2(int a, int b){
    return ((a >= b) ? a : b);
}

int getMax_3(int a, int b){
    int c = a - b;
    int k = (c >> 31) & 0x1;
    int max = a - k * c;
    return max;
}
