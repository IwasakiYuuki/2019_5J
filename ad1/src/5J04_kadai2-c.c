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
    for(int i=0; i<size; i++){
        buf = buf - ((buf - data[i]) & ((buf - data[i]) >> 31));
    }

    return buf;
}

int getMin(int *data, int size) {
    int buf = data[0];
    for(int i=0; i<size; i++){
        buf = buf + ((data[i] - buf) & ((data[i] - buf) >> 31));
    }

    return buf;
}
