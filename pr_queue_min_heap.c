#include<stdio.h>
#include<stdlib.h>

struct Heap{
    int* array;
    int count;
    int capacity;
    
};

struct Heap* createHeap(int capacity){
    struct Heap* h = (struct Heap*)malloc(sizeof(struct Heap));
    h->count = 0;
    h->capacity = capacity;
    h->array = (int*)malloc(h->capacity * sizeof(int));

    return h;
}

int parent(struct Heap *h,int i){
    if(i<=0 || i>=h->count){
        return -1;
    }
    return (i-1)/2;

}

int leftChild(struct Heap* h,int i){
    int left = 2*i + 1;
    if(left >= h->count){
        return -1;
    }
    return left;
}

int rightChild(struct Heap* h,int i){
    int right = 2*i + 2;
    if(right >= h->count){
        return -1;
    }
    return right;
}

int getMin(struct Heap* h){
    if(h->count == 0){
        return -1;
    }
    return h->array[0];
}

void minHeapify(struct Heap* h, int i){
    int l,r,min,temp;

    l = leftChild(h,i);
    r = rightChild(h,i);
    min = i;
    if(l != -1 && h->array[l] < h->array[i])
        min = l;
    
    if(r != -1 && h->array[r] < h->array[min])
        min = r;

    if(min != i){
        temp = h->array[i];
        h->array[i] = h->array[min];
        h->array[min] = temp;

        minHeapify(h,min);
    }

    
}

int deleteMin(struct Heap* h){
    int data;
    if(h->count == 0){
        return -1;
    }
    data = h->array[0];

    h->array[0] = h->array[h->count - 1];
    --h->count;
    minHeapify(h,0);
    return data;
}

int insert(struct Heap* h,int data){
    int i;
    int temp;
    if(h->count > h->capacity){
        //resizeHeap(h);
        return 0;
    }
        
    ++h->count;
    i = h->count - 1;
    h->array[i] = data;
    while(i != 0 && h->array[parent(h,i)] > h->array[i]){
        temp = h->array[i];
        h->array[i] = h->array[parent(h,i)];
        h->array[parent(h,i)] = temp;

        i= parent(h,i);
    }
}

/*
void resizeHeap(struct Heap* h){
    int * array_old = h->array;
    h->array = (int*)malloc(2*h->capacity*sizeof(int));

    for(int i=0;i<h->capacity;i++){
        h->array[i] = array_old[i];
    }
    h->capacity = 2*h->capacity;
    free(array_old);
}
*/
void DestroyHeap(struct Heap* h){
    if(h == NULL){
        return;
    }
    free(h->array);
    free(h);
    h = NULL;
}

int main(){
    struct Heap* h = createHeap(3);
    insert(h,4);
    insert(h,1);
    insert(h,2);
    insert(h,3);

    

    printf("\nMin = %d",getMin(h));


    return 0;
}
