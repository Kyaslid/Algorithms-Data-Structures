#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *my_strdup(const char *s) {
    size_t length = strlen(s) + 1;
    char *duplicate = (char *)malloc(length);
    if (duplicate) {
        strcpy(duplicate, s);
    }
    return duplicate;

}
char *concat(char **s, int n) {
    
    size_t length = 0;
    for (int i = 0; i < n; i++) {
        length += strlen(s[i]);
    }
    
    char *res = (char *)malloc(length + 1);

   int res_index = 0;
    for (int i = 0; i < n; ++i) {
        int index = 0;
        while (s[i][index] != '\0') {
            res[res_index] = s[i][index];
            res_index++;
            index++;
        }
    }
    res[res_index] = '\0';
    return res;
}

char *create_row(char *sign, int n){
    char *res = (char *)malloc(n+1);
    for(int i=0;i<n;i++){
        res[i] = *sign;
    }

    res[n] = '\0';
    return res;
}

char *frame(int heigh, int width, char *str) {
    
    size_t ln = strlen(str);

    if((width < ln+2) || str == "" || heigh<3){
        printf("Error");
        return 0;
    }

    int num_for_str = heigh/2 + heigh%2;
    
    char **matrix = (char **)malloc(width * sizeof(char *));
    char *st_ed = create_row("*", width);
    matrix[0] = st_ed;
    matrix[heigh-1] = st_ed;

    char *void_row = create_row(" ", width-2);

    int num_space = (width - 2 - strlen(str))/2;
    int delt_space = (strlen(str)%2 + width%2)%2;
    char *start_void = create_row(" ", num_space);
    char *last_void = create_row(" ", num_space+delt_space);

    char *default_row[3] = {"*", void_row, "*"};
    for(int i=1;i<heigh-1;i++){
        if(i == num_for_str-1){
            char *row[5] = {"*", start_void, str, last_void, "*"};
            matrix[i] = concat(row, 5);
    
        } else{
            matrix[i] = concat(default_row, 3);
        }
    }

    for(int i=0;i<heigh;i++){
        printf("%s\n", matrix[i]);
    }

    free(start_void);
    free(last_void);
    free(st_ed);
    free(void_row);    
    for(int i=1;i<heigh-1;i++){
        free(matrix[i]);
    }
    free(matrix);
}

int main(int argc, char *argv[]){
    int heigh, width;
    char *endptr1, *endptr2;

    heigh = strtol(argv[1], &endptr1, 10);
    width = strtol(argv[2], &endptr2, 10);
    frame(heigh, width, argv[3]);
    
    return 0;
}
