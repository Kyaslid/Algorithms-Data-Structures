#include <stdio.h>
#include <math.h>

//Код несколько мудреный, тк только начинал учить С

unsigned long long max_step_2(int n){
    //поиск граничного разряда числа
    for (int cnt = 63; cnt; cnt--){
        if (n>=pow(2,cnt)){
            return cnt;
        }
    }
}

unsigned long long cut_num(unsigned long long num, int step){
    //обрезаем число до нужного разряда в двоичке
    unsigned long long two_in_step;
    for (int cnt = 63; (cnt>step & num>0); cnt--){
        two_in_step = pow(2,cnt);
        if (num>=two_in_step){
            num-=two_in_step;
        }
    }
    return num;
}

int what_value(unsigned long long num, int step){ 
    // проверяем есть ли степень двойки в обрезанном (предполагается) числе
    if (num<pow(2,step)){return 0;}
    else{return 1;}
}

int main(void)
{
    unsigned long long a,b,m, a_mod;
    scanf("%llu%llu%llu", &a, &b, &m);
    int mx_st_b = max_step_2(b);
    a_mod = a%m;
    unsigned long long ab = a, cutted_num=b;
    for (int n = mx_st_b; n; n--){
        cutted_num = cut_num(cutted_num,n-1);
        ab = (((ab%m)*(2%m))%m + ((a%m)*(what_value(cutted_num,n-1)%m)%m)%m)%m; //Приложенная к заданию формула
    }
    printf("%llu", ab);
}
