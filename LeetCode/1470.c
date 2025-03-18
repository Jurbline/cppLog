/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* shuffle(int* nums, int numsSize, int n, int* returnSize) {
        if (numsSize != 2 * n) {
        return NULL;
    }
    int* A = (int*)malloc(sizeof(int) * 2 * n);
    if (A == NULL) {
        return NULL;
    }
    *returnSize = 2 * n;
    int mid=n;
    for(int i=0;i<n;i++){
    A[i]=0;
    }
    for(int i=0;i<n;i++){
        A[2*i]=nums[i];
        A[2*i+1]=nums[mid];
        mid++;
    }
    return A;
}
