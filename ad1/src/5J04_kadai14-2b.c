#include <stdio.h>

int countR (int n, int a) {
    if (n==0) return 0;
    int power = 1;
    while (10 * power < n) power *= 10;
    int first = n / power, remainder = n % power;
    int nTwosFirst = 0;
    if (first > a) nTwosFirst += power;
    else if (first == a) nTwosFirst += remainder + 1;
    int nTwosOther = first * countR (power - 1, a) + countR (remainder, a);
    return nTwosFirst + nTwosOther;
}


int countI (int n, int a) {
    int countof2s = 0, digit = 0;
    int num = n, seendigits = 0, position = 0, pow10_pos = 1;
    while (num > 0) {
        digit = num % 10;
        int pow10_posMinus1 = pow10_pos / 10;
        countof2s += digit * position * pow10_posMinus1;
        if (digit == a) countof2s += seendigits + 1;
        else if (digit > a) countof2s += pow10_pos;
        seendigits = seendigits + pow10_pos * digit;
        pow10_pos *= 10;
        position++;
        num = num / 10;
    }
    return countof2s;
}

int main(){
    printf("countR = %d\n",countR(99, 2));
    printf("countL = %d\n",countI(99, 2));
    return 0;
}
