#include <stdio.h>

int global_start=0;
int global_end=0;

int getMaxProduct(int a[], int size) {
	int i;
	int max_product=0, product=1, length=0;
	for(i=0;i<size;i++){
		if(a[i] == 0){
			product = 1;
			length=0;
		}else{
			product *= a[i];
			if(max_product < product){
				max_product = product;
				global_end = i;
				length++;
			}else if(max_product < a[i]){
				max_product = a[i];
			}
		}
	}
	global_start = global_end-length-1;
	return max_product;
}

int main(void) {
	int i, size = 6;
	int data[] = {1,-1,5,5,-2,-1};
	printf("INPUT:{");
	for (i = 0; i < size-1; i++) {
		printf("%d,", data[i]);
	}
	printf("%d",data[i]);
	printf("}\n");
	printf("OUTPUT:%d {",getMaxProduct(data,size));
	for (i = global_start; i < global_end; i++) {
		printf("%d,", data[i]);
	}
	printf("%d",data[i]);
	printf("}\n");
}
