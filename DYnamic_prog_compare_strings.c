#include<stdio.h>
#include<stdlib.h>


int fib(int n){

    int fib_map[n+1];

    fib_map[0] = 0;
    fib_map[1] = 1;

    for(int i=2;i<=n;i++){
        fib_map[i] = fib_map[i-1] + fib_map[i-2];
    }

    return(fib_map[n]);
}

int LCW(const char* W1,int m,const char*W2,int n){
    int LCS[m+1][n+1];
    for(int r=0;r<=m;r++){
        LCS[r][n] = 0;
    }

    for(int c=0;c<=n;c++){
        LCS[m][c] = 0;
    }

    int maxLCS = 0;

    for(int c=n-1;c>=0;c--){
        for(int r=m-1;r>=0;r--){
            if(W1[r] == W2[c]){
                LCS[r][c] = 1 + LCS[r+1][c+1];
            }

            else
                LCS[r][c] = 0;

            if(LCS[r][c] > maxLCS)
                maxLCS = LCS[r][c];
        }
    }


    for(int i=0;i<=m;i++){
        for(int j=0;j<=n;j++){
            printf("%d ",LCS[i][j]);
        }
        printf("\n");
    }

    return(maxLCS);
}



int LCW_more(const char* W1,int m,const char*W2,int n){
    int LCS[m+1][n+1];
    for(int r=0;r<=m;r++){
        LCS[r][n] = 0;
    }

    for(int c=0;c<=n;c++){
        LCS[m][c] = 0;
    }

    int maxLCS = 0;

    for(int c=n-1;c>=0;c--){
        for(int r=m-1;r>=0;r--){
            if(W1[r] == W2[c]){
                LCS[r][c] = 1 + LCS[r+1][c+1];
            }
            else{
                //LCS[r][c] = max(LCS[r+1][c],LCS[r][c+1]);
                if(LCS[r+1][c] >= LCS[r][c+1]){
                    LCS[r][c] = LCS[r+1][c];
                }
                else{
                    LCS[r][c] = LCS[r][c+1];
                }
            }

            if(LCS[r][c] > maxLCS)
                maxLCS = LCS[r][c];
        }
    }


    for(int i=0;i<=m;i++){
        for(int j=0;j<=n;j++){
            printf("%d ",LCS[i][j]);
        }
        printf("\n");
    }

    return(maxLCS);
}



int main(){

    
    const char* W1 = (char*)malloc(7*sizeof(char));
    W1 = "bisect\0";

   
    const char* W2 = (char*)malloc(7*sizeof(char));
    W2 = "secret\0";

    printf("\nLCW of W1 and W2 = %d",LCW(W1,6,W2,6));
    printf("\nLCW_more of W1 and W2 = %d",LCW_more(W1,6,W2,6));






    return 0;
}
