#include<iostream>
using namespace std;

struct Node{
    int data;
    Node* next;
};

void enQueue(Node** root, int x){
    
    Node* newNode = new Node;
    newNode->data = x;
    newNode->next = NULL;

    if(*root == NULL){
        cout << "\nQueue is empty" << endl; 
        *root = newNode;
        cout << "\nenQueue " << x << " to Queue" << endl;
        return;
        
    }

    cout << "\nenQueue " << x << " to Queue" << endl;
    

    Node* temp = *root;
    while(temp->next != NULL){
        temp = temp->next;
    }

    temp->next = newNode;

    return;

}


int deQueue(Node** root){

    if(*root == NULL){
        cout << "\nQueue is empty" << endl; 
        return 0;
    }
    
    Node* temp = *root;
    *root = (*root)->next;
    int m = temp->data;
    delete(temp);
    cout << "\ndeQueue " << m << " from Queue" << endl;
    return m;

    
}

int front(Node* root){
    if(root == NULL){
        cout << "\nQueue is empty" << endl; 
        return 0;
    }

    return root->data;
}

int rear(Node* root){

    if(root == NULL){
        cout << "\nQueue is empty" << endl; 
        return 0;
    }

    Node* temp = root;
    while(temp->next != NULL){
        temp = temp->next;
    }

    return temp->data;
}

int Qsize(Node* root){

    if(root == NULL){
        return 0;
    }

    Node* temp = root;
    int l = 0;
    while(temp != NULL){
        ++l;
        temp = temp->next;
    }
    return l;
}

void reverse()


struct stack{
    Node* Q1;
    Node* Q2;
};

void push(stack* S, int x){
    cout << "\n" << x << " pushed to stack" << endl;
    enQueue(&S->Q1,x);

}

int pop(stack* S){

    Node* temp = NULL;

    if(Qsize(S->Q1) == 0){
        return 0;
    }
    int m;
    while(Qsize(S->Q1) != 1){
        m = deQueue(&S->Q1);
        enQueue(&S->Q2,m);
        
    }
    int a = deQueue(&S->Q1);

    temp = S->Q1;
    S->Q1 = S->Q2;
    S->Q2 = temp;
    cout << "\n" << a << " popped out of stack" << endl;
    return a;



}



int main(){

    /*
    Node* Q = NULL;

    enQueue(&Q,1);
    enQueue(&Q,2);
    enQueue(&Q,3);
    enQueue(&Q,4);
*/

    stack* S = new stack;
    S->Q1 = NULL;
    S->Q2 = NULL;

    push(S,1);
    push(S,2);
    push(S,3);
    push(S,4);
    cout << "\n popped = " << pop(S);
    cout << "\n\n ..popped = " << pop(S);



}

