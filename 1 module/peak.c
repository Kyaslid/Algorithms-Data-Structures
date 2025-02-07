unsigned long peak(unsigned long nel,
        int (*less)(unsigned long i, unsigned long j)){
        unsigned long left=0 , right = nel-1, mid;

        while(left<right){
            mid = left + (right-left)/2;

            if(less(mid,mid+1)){
                left = mid+1;
            } else{
                right = mid;
            }
        }
        return left;
}
