#include <stdio.h>


int add_no_arithm(int a,int b){
    if(b==0)return a;
    int s = a^b;
    int c = (a&b)<<1;
    return add_no_arithm(s,c);
}

int sub_with_add(int x,int y){
    int minus = add_no_arithm(~y,1);    //2の補数
    return add_no_arithm(x,minus);
}

int sub_without_add(int x,int y){
    while(y!=0){
        int carry = (~x & y) << 1;
        x ^=y;
        y = carry;
    }
    return x;
}

int mul(int x,int y){
    int ans = 0;
    int flag=1;
    if(x<0){
        x = add_no_arithm(~x,1);
        flag = add_no_arithm(~flag,1);
    }
    if(y<0){
        y = add_no_arithm(~y,1);
        flag = add_no_arithm(~flag,1);
    }
    for(int i=0;i<31;i=add_no_arithm(i,1)){
        if((y>>i)&0x1){
            int shift = x << i;
            ans = add_no_arithm(ans,shift);
        }
    }
    if(flag == -1){
        ans =  add_no_arithm(~ans, 1);
    }
    return ans;
}

void div(int x,int y){
    int cnt=0;
    int f=1;
    int buf_x=x;
    int buf_y=y;
    if(x<0){
        x = add_no_arithm(~x,1);
        f = add_no_arithm(~f,1);
    }
    if(y<0){
        y = add_no_arithm(~y,1);
        f = add_no_arithm(~f,1);
    }
    while(x>y){
        x = sub_with_add(x,y);
        cnt = add_no_arithm(cnt,1);
    }
    int q = cnt;
    int r = x;
    printf(
        "割り算：%d / %d = %d 余り %d\n",
        buf_x,
        buf_y,
        q*f,
        r
    );
}

int main(){
    int a=10,b=3;
    int c=-20,d=-6;
    printf("足し算：%d + %d = %d\n",a,b,add_no_arithm(a,b));
    printf("引き算：%d - %d = %d\n",a,b,sub_with_add(a,b));
    printf("引き算（関数なし）：%d - %d = %d\n",a,b,sub_without_add(a,b));
    printf("掛け算：%d * %d = %d\n",a,b,mul(a,b));
    div(a,b);
    div(a,d);
    div(a,b);
    div(a,d);
}
