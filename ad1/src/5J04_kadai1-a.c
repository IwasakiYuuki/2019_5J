#include <stdio.h>
#include <time.h>

void swap_1(int a, int b);
void swap_2(int a, int b);
void swap_3(int a, int b);

int main(){
    clock_t start, end;
    start = clock();
    swap_1(3, 2);
    end = clock();
    printf("time = %lf\n", (double)(end-start)/CLOCKS_PER_SEC);
    start = clock();
    swap_2(3, 2);
    end = clock();
    printf("time = %lf\n", (double)(end-start)/CLOCKS_PER_SEC);
    start = clock();
    swap_3(3, 2);
    end = clock();
    printf("time = %lf\n", (double)(end-start)/CLOCKS_PER_SEC);
    return 0;
}


void swap_1(int a, int b) {
    int tmp = a;
    a = b;
    b = tmp;

    printf("a: %d, b: %d \n", a, b);
}

void swap_2(int a, int b) {
    a=b-a;
    b=b-a;
    a=a+b;

    printf("a: %d, b: %d \n", a, b);
}

void swap_3(int a, int b) {
    a = a^b;
    b = a^b;
    a = a^b;

    printf("a: %d, b: %d \n", a, b);
}
