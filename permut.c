#include <stdio.h>
static int mass_perm[40320];
int j = 0;

int compare_mass(int* mass_a, int* mass_b, int n){
    for(;n;n--){
        if(mass_a[n-1] != mass_b[n-1]){
            return 0;
        }
    }
    return 1;}

int print_mass(int* mass, int n){
  for(int i=0;i<n;i++){
      printf("%d",mass[i]);
  }
}

char permutations(int* ref, int* res, int* ins, int* check, int iter){
    if (iter >= 8){    
       //print_mass(res,8);
       //printf("\n");
       mass_perm[j] = compare_mass(res, ref, 8);
       j++;
    }

    for(int i=8;i;i--){
        if(check[i-1]==0){
            res[iter] = ins[i-1];
            check[i-1] = 1;
            permutations(ref, res,ins,check,iter+1);
            check[i-1] = 0;
        }
    }
}

int main(){
    int mass_a[8], mass_b[8], q[8],checker[8] = {0};
    int answ=0;
    for(int i=0;i<8;i++){
        scanf("%d", &mass_a[i]);}
    for(int i=0;i<8;i++){
        scanf("%d", &mass_b[i]);}    
    
    permutations(mass_a, q, mass_b, checker, 0);

    for(int i=0;i<40320;i++){
        answ += mass_perm[i];
    }
    if(answ>0){
        printf("%s", "yes");
    } else{
        printf("%s", "no");
    }

}
