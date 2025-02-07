#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int wcount(char *s){
    size_t lenth_row = strlen(s);
    int cnt=0;
    if(s == "" || lenth_row == 0){
        return 0;
    } else{
        if(!isspace(s[0])){
            cnt++;
        }
        for(int i=0; i+1<lenth_row;i++){
             if(isspace(s[i]) && !isspace(s[i+1])){
                 cnt++;
             } 
        }
        return cnt;
    }
}

int main() {
    char str[1000];
    int q;
    
    fgets(str, sizeof(str), stdin);
    q = wcount(str);
    printf("%d\n",q);
}
