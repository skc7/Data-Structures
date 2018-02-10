#include<iostream>
#include<math.h>

using namespace std;


void reverseArray(int arr[], int a){
    int l = 0;
    l = a;
    
    int temp;
    for(int i=0; i<l/2; i++){
        temp = arr[i];
        arr[i] = arr[l-i-1];
        arr[l-i-1] = temp;
        cout<<"\na[" << i << "]" << arr[i]<<endl;
        cout<<"\na["<<l-i-1<<"]"<<arr[l-i-1]<<endl;
    }
}



int main(){

    int a[] = {1,2,3,4,5,6,7};
    int n = sizeof(a)/sizeof(int);
    cout<<"\nlength = "<<n<<endl;
    reverseArray(a,n);

    for(int j=0;j<7;j++){
        cout<<a[j]<<" ";
    }



}