#include<iostream>
#include<limits.h>
using namespace std;
#define max 1000



struct Node{
    int data;
    Node* next;
};

int isEmpty(Node* root){
    return !root;
}

void push(Node** root, int x){
    Node* newNode = new Node;
    newNode->data = x;
    newNode->next = NULL;

    newNode->next = *root;
    *root = newNode;
    
    cout << "\n" << x << " pushed to stack" << endl;

}

int pop(Node** root){

    if(isEmpty(*root)){
        cout << "\nstack underflow" << endl;
    }

    Node* temp = *root;
    *root = (*root)->next;
    int popped = temp->data;
    delete(temp);
    cout << "\n" << popped << " popped out of stack" << endl;
    return popped;

}

int peek(Node* root){
    
        if(isEmpty(root)){
            cout << "\nstack underflow" << endl;
        }

        return root->data;
}

int stack_length(Node* root){
    
    Node* temp = root;
    int l = 0;
    while(temp != NULL){
        ++l;
        temp = temp->next;
    }
    return l;


}



struct queue{
    Node* s1;
    Node* s2;
};

void enQueue(queue* q, int x){
    cout << "\nEnqueue " << x << " to queue" << endl;
    push(&q->s1,x);
}

int deQueue(queue* q){

    if(q->s1 == NULL && q->s2 == NULL){
        cout << "\nQueue is empty" << endl;
        return 0;
    }

    int m;

    if(q->s2 == NULL){
        while(q->s1 != NULL){
            m = pop(&q->s1);
            push(&q->s2,m);
        }

    }
    

    m = pop(&q->s2);
    cout << "\nDequeue " << m << " from queue" << endl;
    return m;
}


void insertAtBottom(Node** S, int item){
    if(isEmpty(*S)){
        push(S,item);
    }

    else{
        int temp = pop(S);
        insertAtBottom(S,item);
        push(S,temp);
    }
}

void reverse(Node** S){
    if(isEmpty(*S)){
        return;
    }

    else{
        int temp = pop(S);
        reverse(S);
        insertAtBottom(S,temp);
    }


}

void sortedInsert(Node** S, int temp){
    if(isEmpty(*S) || temp > peek(*S)){
        push(S,temp);
        return;
    }

    else{
        int a = pop(S);
        sortedInsert(S,temp);
        push(S,a);
    }
}

void sort(Node** S){
    if(isEmpty(*S)){
        return;
    }
    
    else{
        int temp = pop(S);
        sort(S);
        sortedInsert(S,temp);
    }
}

int main(){

    Node* root = NULL;

    push(&root,8);
    push(&root,1);
    push(&root,6);
    push(&root,2);
    


    //insertAtBottom(&root,5);
    //reverse(&root);
    sort(&root);
    cout << "\nAfter sort " << endl;
    pop(&root);
    pop(&root);
    pop(&root);
    pop(&root);
    pop(&root);
  
  
  
    //cout << "\nstack length = " << stack_length(root) << endl;
/*
    queue* q = new queue;
    q->s1 = NULL;
    q->s2 = NULL;

    enQueue(q,1);
    enQueue(q,2);
    enQueue(q,3);
    enQueue(q,4);
*/



}
