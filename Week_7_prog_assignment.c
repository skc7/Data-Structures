#include<stdio.h>
#include<stdlib.h>


int diff(int a,int b){
    int x = a - b;
    if(x < 0){
        x = -1 * x;
    }

    return x;
}


int weight(int** A,int i,int HV){//V=0 H=1
    int w = 0;
    if(HV == 0){
        //printf("\nHV=0");
        w = diff(A[0][i],A[1][i]);
    }

    else{
        //printf("\nHV=1");
        w = diff(A[0][i],A[0][i+1]) + diff(A[1][i],A[1][i+1]);
    }
    return w;
}

int max(int a,int b){
    if(a > b){
        return a;
    }

    else 
        return b;
}

int totalWeight(int** A,int start,int N){
    int total=0;
    int X;
    int Y;

    if(start == N-1){
        return weight(A,N-1,0);
    }
    if(start<N){
        //X = weight(A,start,0) + totalWeight(A,start+1,N)
        //Y = weight(A,start,1) + totalWeight(A,start+2,N)

        X = weight(A,start,0);
        Y = weight(A,start,1);
        
        if(X>Y)
            total = total + X + totalWeight(A,start+1,N);
        else    
            total = total + Y + totalWeight(A,start+2,N);
        
    }
    return total;
}

int totalWeight_1(int** A,int start,int N){
    int total=0;
    int X;
    int Y;

    if(start == N-1){
        return weight(A,N-1,0);
    }

    if(start > N-1){
        return 0;
    }

    if(start<N){
        X = weight(A,start,0) + totalWeight_1(A,start+1,N);
        Y = weight(A,start,1) + totalWeight_1(A,start+2,N);

        //X = weight(A,start,0);
        //Y = weight(A,start,1);
        
        total = total + max(X,Y);
        
    }
    
    
    return total;
}

int main(){
    int N;
    scanf("%d",&N);

    int** A = (int**)malloc(2*sizeof(int*));
    for(int i=0;i<N;i++){
        A[i] = (int*)malloc(N*sizeof(int));
    }

    //int A[2][N];

    int i=0;
    char temp;
    while(temp != '\n'){
        scanf("%d%c",&A[0][i],&temp);
        ++i;
    }

    i=0;
    char temp1;
    while(temp1 != '\n'){
        scanf("%d%c",&A[1][i],&temp1);
        ++i;
    }

    int* DP = (int*)malloc(N*sizeof(int));

    DP[0] = diff(A[0][0],A[1][0]);
    DP[1] = max(  DP[0] + diff(A[0][1],A[1][1])  ,  diff(A[0][0],A[0][1]) + diff(A[1][0],A[1][1]) );

    for(int i=2;i<N;i++){
        //printf("\ni=%d",i);
        DP[i] = max( DP[i-1] + diff(A[0][i],A[1][i])  ,  DP[i-2] + diff(A[0][i-1],A[0][i]) + diff(A[1][i-1],A[1][i]));
    }

    printf("%d\n",DP[N-1]);
    //printf("%d\n",totalWeight_1(A,0,N));

    return 0;
}
