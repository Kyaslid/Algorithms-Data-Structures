#include <stdio.h>

unsigned int create_set(int cnt) {
    unsigned int set = 0;
    int a;
    for (; cnt; cnt--) {
        scanf("%i", &a);
        set |= (1U << a);
    }
    return set;
}

void decode_result_set(unsigned int set) {
    int first = 1;
    for (int i = 0; i < 32; i++) {
        if (set & (1U << i)) {
            if (!first) {
                printf(" ");
            }
            printf("%d", i);
            first = 0;
        }
    }
    printf("\n");
}

int main(void) {
    int cnt_A, cnt_B;
    unsigned int set_A, set_B, result_set;

    scanf("%i", &cnt_A);
    set_A = create_set(cnt_A);

    scanf("%i", &cnt_B);
    set_B = create_set(cnt_B);

    result_set = set_A & set_B;

    decode_result_set(result_set);
    return 0;
}
