#include<stdio.h>
#include<stdlib.h>

int max(int a,int b){
    if(a >= b) return a;

    else return b;
}

int knapsack(int W,int wt[],int val[],int n){
    if(n==0 || W==0){
        return 0;
    }

    if(wt[n-1] > W){
        return knapsack(W,wt,val,n-1);
    }

    else return max( val[n-1] + knapsack(W - wt[n-1],wt,val,n-1), knapsack(W,wt,val,n-1) );
}


int main(){

    int val[3] = {60,10,120};
    int weight[3] = {10,20,30};
    int w = 50;

    printf("\nknap = %d",knapsack(w,weight,val,3));


    return 0;
}
