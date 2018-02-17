#include<iostream>
using namespace std;




int binary_search(int a[], int l,int r,int x){
    if(r > l){
        int mid = l + (r-l)/2;

        if(a[mid] == x)
            return mid;

        if(a[mid] > x)
            return binary_search(a,l,mid-1,x);

        return binary_search(a,mid+1,r,x);
    }

    return -1;



}

void swap(int a[],int pos1, int pos2){
    int temp = 0;
    temp = a[pos1];
    a[pos1] = a[pos2];
    a[pos2] = temp;
}


void BubbleSort(int A[],int len){
    for(int i=0; i<len-1 ; i++){
        for(int j=0;j<len-2;j++){
            if(A[j] > A[j+1]){
                swap(A,j,j+1);
            }
        }
    }
}

void selectionSort(int a[],int len){
    int sPOS = 0;
    int endPOS = len -1;
    int minPOS = 0;

    for(int i = 0; i < len; i++){
        for(int j = i+1; j< len; j++){
            if(a[j] < a[i])
                swap(a,i,j);
            }
    }
}

void InsertionSort(int a[],int len){

    for(int i=1;i<len;i++){
        int j = i;
        while(j >0 && a[j] < a[j-1]){
            swap(a,j,j-1);
            j = j-1;
        }
    }
}

void Insert(int A[], int start){
    int j = start;
    while(j > 0 && A[j] < A[j-1]){
        swap(A,j,j-1);
        j = j-1;
    }
}

void InsertionSort_rec(int A[],int start, int n){
    if(start > n-1){
        return;
    }
    Insert(A,start);
    InsertionSort_rec(A,start+1,n);
    return;
}

void Merge(int A[], int l, int m, int r){

    int n1 = m-l+1;
    int n2 = r-m;
    int i,j,k;
    int L[n1], R[n2];
    for(i=0;i<n1;i++){
        L[i] = A[l+i];
    }

    for(j=0;j<n2;j++){
        R[j] = A[m+1+j];
    }

    i=0;
    j=0;
    k=l;

    while(i<n1 &&j <n2){
        if(L[i] < R[j] ){
            A[k] = L[i];
            i++;
        }

        if(L[i] > R[j] ){
            A[k] = R[j];
            j++;
        }
        k++;
    }

    while(i<n1){
        A[k] = L[i];
        i++;
        k++;
    }

    while(j<n2){
        A[k] = R[j];
        j++;
        k++;
    }


}

void MergeSort(int A[], int l, int r){

    if(l < r){
        int m = (l + r)/2;
        MergeSort(A,l,m);
        MergeSort(A,m+1,r);
        Merge(A,l,m,r);
    }
    return;

}


int Partition(int *A,int start, int end){
    int pivot = A[end];
    int partitionIndex = start;
    for(int i= start; i<end; i++){
        if(A[i] < pivot){
            swap(A,i,partitionIndex);
            partitionIndex++;
        }
    }
    swap(A,partitionIndex,end);
    return partitionIndex;
}


void QuickSort(int *A, int start, int end){
    if(start >= end)
        return;
    int partitionIndex = Partition(A,start,end);
    QuickSort(A,start,partitionIndex-1);
    QuickSort(A,partitionIndex+1,end);
    



}


int main(){

    int a[] = {8,7,6,5,4,3};
    int x = 6;

    QuickSort(a,0,5);


    for(int i=0; i<6;i++){
        cout << " " << a[i];
    }


    


    return 0;
}
