#include <stdio.h>

int global_start=0;
int global_end=1;
int getMaxSum(int a[], int size) {
	int i;
	int max_sum = a[0];
	int sum = a[0];
	for (i = 1; i < size; i++) {
		sum += a[i];
		if (max_sum < sum){
			max_sum = sum;
			global_end++;
		}
		if(sum < a[i]){
			sum = a[i];
			global_start = i;
		}
	}
	return max_sum;
}

int main(void) {
	int i;
	int size = 5;
	int d[] = {1,2,3,8,-2};
	printf("INPUT:{");
	for (i = 0; i < size-1; i++) {
		printf("%d,", d[i]);
	}
	printf("%d",d[i]);
	printf("}\n");
	printf("OUTPUT:%d {",getMaxSum(d, size));
	for (i = global_start; i < global_end; i++) {
		printf("%d,", d[i]);
	}
	printf("}\n");
}
