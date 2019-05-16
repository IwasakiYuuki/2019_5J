#include <stdio.h>

int getMax(int *data, int size);
int getMin(int *data, int size);

int main() {
    int data[7] = {10, 21, 13, 4, 5, 1, 2};
    int n = 7;

    printf("max=%d, min=%d\n", getMax(data, n), getMin(data, n));
    return 0;
}

int getMax(int *data, int size) {
    int buf = data[0];
    do{
        buf = buf - ((buf - *data) & ((buf - *data) >> 31));
        data++;
    }while(--size);

    return buf;
}

int getMin(int *data, int size) {
    int buf = data[0];
    do{
        buf = buf + ((*data - buf) & ((*data - buf) >> 31));
        data++;
    }while(--size);

    return buf;
}
