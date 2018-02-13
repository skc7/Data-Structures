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

int main(){

    int a[] = {8,7,6,5,4,3};
    int x = 6;

    InsertionSort(a,6);


    for(int i=0; i<6;i++){
        cout << " " << a[i];
    }


    


    return 0;
}
