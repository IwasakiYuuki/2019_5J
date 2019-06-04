#include<stdio.h>
#include "MT.h"

int global_counter3 = 0;
int global_counter4 = 0;

int rand5() {
    return genrand_int32() % 5;
}

int rand7_2(){
    int v = rand5() + rand5();
    return (v%7+1);
}

int rand7_3(){
    while(1){
        int num = 5 * rand5() + rand5();
        global_counter3 = global_counter3 + 2;
        if(num < 21) return (num%7)+1;
    }
}

int rand7_4(){
    while(1){
        int num = 2*rand5();
        int odd = rand5();
        global_counter4 = global_counter4 + 2;
        if(odd != 4){
            num = num + odd %2;
            if(num < 7) return num+1;
        }
    }
}

int main(void) {
    printf("乱数生成結果\n");
    printf("2 { ");
    for (int i = 0; i < 10; i++) {
        printf("%d ",rand7_2());
    }
    printf("}\n");

    printf("3 { ");
    for (int i = 0; i < 10; i++) {
        printf("%d ",rand7_3());
    }
    printf("}\n");

    printf("4 { ");
    for (int i = 0; i < 10; i++) {
        printf("%d ",rand7_4());
    }
    printf("}\n");

    printf("rand5()呼び出し回数の平均：試行回数1000\n");
    global_counter3 = 0;
    global_counter4 = 0;

    for(int i=0;i<1000;i++){
        rand7_3();
        rand7_4();
    }
    printf("3 [%lf]\n",(double)global_counter3/1000);
    printf("4 [%lf]\n",(double)global_counter4/1000);
    return 0;
}