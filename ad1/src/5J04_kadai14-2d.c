#include <stdio.h>

int mul_all(int num){
    int i, ans=1;
    int buf1 = num;
    int buf2;
    do{
        buf2 = buf1 / 10;
        ans *= (buf1 - buf2*10);
        buf1 = buf2;
    }while(buf1 >= 10);
    ans *= buf1;
    return ans;
}

int add_all(int num){
    int i, ans=0;
    int buf1 = num;
    int buf2;
    do{
        buf2 = buf1 / 10;
        ans += (buf1 - buf2*10);
        buf1 = buf2;
    }while(buf1 >= 10);
    ans += buf1;
    return ans;
}

int main(){
    printf("mul test %d\n", mul_all(114514));
    printf("add test %d\n", add_all(114514));
    return 0;
}
