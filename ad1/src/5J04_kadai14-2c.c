#include <stdio.h>

int count_num(int s, int e){
    int buf, count=0;
    for(int i=s; i<=e; i++){
        buf = i;
        do{
            buf = buf / 10;
            count++;
        }while(buf > 0);
    }
    return count;
}

int main(){
    printf("345 =%d\n", count_num(3, 5));
    printf("78  =%d\n", count_num(7, 8));
    printf("0~10=%d\n", count_num(0, 10));
    return 0;
}
