#include <stdio.h>

int getMax (int a, int b, int c) {
    a = a - ((a - b) & ((a - b) >> 31));
    return a - ((a - c) & ((a - c) >> 31));
}
int getMin (int a, int b, int c) {
    b = b + ((a - b) & ((a - b) >> 31));
    return b + ((c - b) & ((c - b) >> 31));
}

int main (void) {
    int a = 5, b = 10, c = 7;
    int max, min, med;
    max = getMax (a, b, c);
    min = getMin (a, b, c);
    med = a + b + c - max - min;
    printf ("max = %d, med = %d, min = %d \n", max, med, min);

    return 0;
}