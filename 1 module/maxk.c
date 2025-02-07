#include <stdio.h>

int main(void){
    int n, k;
    scanf("%d", &n);
    int arr[n];
    for(int i=0;i<n;i++){
        scanf("%d", &arr[i]);
    }

    scanf("%d",&k);
    long long sum=0, max_sum;

    for(int i=0;i<k;i++){
        sum+=arr[i];
    }
    max_sum = sum;

    for(int i=k;i<n;i++){
        sum+= arr[i] - arr[i-k];
        if(max_sum < sum){
            max_sum=sum;
        }
    }

    printf("%lld\n", max_sum);
}   
