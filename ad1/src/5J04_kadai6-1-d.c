#include <stdio.h>

int global_start=0;
int global_end=0;

int getMaxProduct(int a[], int size) {
	int i;
	int max_product = 0;
	int product = 1;
	int l = 0;
	int h = 1;
	for(i=0;i<size;i++){
		if(a[i] == 0){
			product = 1;
			l=0;
		}else{
			product *= a[i];
			if(h>0 && product <0){
				h = product;
				global_start = i+1;
			}
			if(max_product < product){
				max_product = product;
				global_end = i;
				l++;
			}else if(max_product < a[i]){
				max_product = a[i];
			}
		}
	}
	if(max_product < (product/h)){
		global_end = size-1;
		max_product = product/h;
	}else{
		global_start = global_end-l-1;
	}
	return max_product;
}

int main(void) {
	int i;
	int size = 6;
	int data[] = {1,-3,3,1,-2,8};
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
