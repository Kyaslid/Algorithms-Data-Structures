#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int min(int a, int b){
    if(a<b){
        return a;
    } else{
        return b;
    }
}

int strdiff(char *a, char *b){
    size_t lenth_mn = min(strlen(a), strlen(b));
    int bit_pos = 0;

     while (*a != '\0' && *b != '\0') {
            unsigned char diff = *a ^ *b;
            if(diff != 0){
                while ((diff & 1) == 0) {
                    diff >>= 1;
                    bit_pos++;
                }
                return bit_pos;
            }
            a++;
            b++;
            bit_pos+=8;
    }
    while (*a != '\0' || *b != '\0') {
        unsigned char diff = *a ^ *b;
        while ((diff & 1) == 0) {
            diff >>= 1;
            bit_pos++;
        }
        return bit_pos;
    }
    return -1;
}

int main() {
    char *abc = "aa", *qwe = "ai";
    printf("%d\n", strdiff(abc, qwe));
    return 0;
}
