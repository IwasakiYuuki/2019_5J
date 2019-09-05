#include <stdio.h>

int count2sR (int n) {
    if (n==0) return 0;
    int power = 1;
    while (10 * power < n) power *= 10;
    int first = n / power, remainder = n % power;
    int nTwosFirst = 0;
    if (first > 2) nTwosFirst += power;
    else if (first == 2) nTwosFirst += remainder + 1;
    int nTwosOther = first * count2sR (power - 1) + count2sR (remainder);
    return nTwosFirst + nTwosOther;
}


int count2sI (int n) {
    int countof2s = 0, digit = 0;
    int num = n, seendigits = 0, position = 0, pow10_pos = 1;
    while (num > 0) {
        digit = num % 10;
        int pow10_posMinus1 = pow10_pos / 10;
        countof2s += digit * position * pow10_posMinus1;
        if (digit == 2) countof2s += seendigits + 1;
        else if (digit > 2) countof2s += pow10_pos;
        seendigits = seendigits + pow10_pos * digit;
        pow10_pos *= 10;
        position++;
        num = num / 10;
    }
    return countof2s;
}

void main(){
    printf("count2sR = %d\n",count2sR(99));
    printf("count2sL = %d\n",count2sI(99));
}
