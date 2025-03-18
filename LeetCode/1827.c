int minOperations(int* nums,int numsSize){
    int temp=0;
    int max=nums[0],count=0;
    for(int i=1;i<numsSize;i++){
        if(nums[i]<=max){
            count=count+(max+1-nums[i]);
            nums[i]=max+1;
            max++;
        }
        else if(nums[i]>max) max=nums[i];
    }
    return count;
}
