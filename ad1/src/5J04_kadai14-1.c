#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void pickMRand (int* original, int* subset, int n, int m);
int Rand (int lower, int higher);
void pickMRand_2 (int* original, int* subset, int n, int m);

int size = 10;

int main(){
    int org[20] = {10,13,22,23,4,51,6,5,81,9,10,1,4,11,14,15,6,37,18,20};
    int sub1[size];
    int sub2[size];
    pickMRand(org,sub1,20,size);
    pickMRand_2(org,sub2,20,size);
    printf("課題  2 | 4\n");
    for(int i=0;i<size;i++){
        printf("%2d: %2d || %2d\n",i,sub1[i],sub2[i]);
    }
    
}

void pickMRand (int* original, int* subset, int n, int m) {
    for (int i = 0; i < m; i++) {
        int index = (int)(rand() % n);
        subset[i] = original[index];
    }
}

int Rand (int lower, int higher) {
    return lower + (int)(rand() % (higher-lower +1));
}

void pickMRand_2 (int* original, int* subset, int n, int m) {
    int array[n];
    memcpy(array, original, sizeof(int)*n);
    for (int i=0; i<m; i++) {
        int index = Rand (i, n-1);
        subset[i] = array[index];
        array[index] = array[i];
    }
}
