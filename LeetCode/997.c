int findJudge(int n, int** trust, int trustSize, int* trustColSize) {
    int* inDegrees = (int *)malloc(sizeof(int)*(n+1));
    int* outDegrees = (int *)malloc(sizeof(int)*(n+1));
    for(int i=0;i<=n;i++){
        inDegrees[i]=0;
        outDegrees[i]=0;
    }
    for(int j=0;j<trustSize;j++){
        int x=trust[j][0];
        int y=trust[j][1];
        ++inDegrees[y];
        ++outDegrees[x];
    }
    for(int i=1;i<=n;i++){
        if(inDegrees[i] == n-1 && outDegrees[i] == 0){
            free(inDegrees);
            free(outDegrees);
            return i;
        }
    }
    free(inDegrees);
    free(outDegrees);
    return -1;
}
