#include <stdio.h>

int main(void)
{
    long long n, x, an, a;
    scanf("%lld%lld%lld", &n, &x, &an);
    long long answ = an;
    long long answ_proizv = an*n;
    for (long long i=n;i>0;i--){
        scanf("%lld",&a);
        answ = (answ*x + a);
        answ_proizv = (answ_proizv*x + a*(i-1));
    }
    answ_proizv /=x;
    printf("%lld\n", answ);

    printf("%lld", answ_proizv);
}
//3**2 + 2*3 +1 --> 2 3 1 2 1
//2*4**3 + 3*4**2 -8*4 - 23 --> 3 4 2 3 -8 -23
