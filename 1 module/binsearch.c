unsigned long binsearch(unsigned long nel, int (*compare)(unsigned long i)){
    unsigned long left=0, right = nel, mid;
    int compare_res;

    while(left<right){
        mid = left + (right - left) / 2;

        compare_res = compare(mid);

        if(compare_res == 0){
            return mid;
        } else if(compare_res<0){
            left = mid+1;
        } else{
            right = mid;
        }
    }
    return nel;
}
