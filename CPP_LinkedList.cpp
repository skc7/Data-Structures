#include <iostream>
#include <math.h>
using namespace std;

//simple C rule: if you want to modify local variable of one function inside another function, pass pointer to that variable.



struct Node{

    int data;
    Node* next;

};



void printList(Node* head_ref){
    Node* temp = head_ref;

    if(temp == NULL){
        cout << "\nLL is empty\n";
        return;
    }
    while(temp != NULL){
        cout << temp->data <<"->";
        temp = temp->next;
    }
    cout<<"NULL\n";

    return;
}

void push(Node** head_ref, int newData){

    Node* new_node = new Node;
    new_node->data = newData;
    new_node->next = NULL;

    if(head_ref == NULL){
        *head_ref = new_node;
        return;
    }

    else{
        new_node->next = *head_ref;
        *head_ref = new_node;
        return;

    }

    }



void append(Node** head_ref, int newData){
    Node* newNode = new Node;
    newNode->data = newData;
    newNode->next = NULL;
    
    Node* temp = *head_ref;
            
    if(*head_ref == NULL){
        *head_ref = newNode;
        return;
                
    }
    
    while(temp->next != NULL){
        temp = temp->next;
    }
    
    temp->next = newNode;
    
    return;
            
    }


void insertAfter(Node* head_ref, Node* node_b, int newData){
        
        Node* newNode = new Node;
        newNode->data = newData;
        newNode->next = NULL;
        
        Node* temp = head_ref;
        if(node_b == NULL){
            return;
        }
        
        while(temp != node_b){
            temp = temp->next;
        }
        
        newNode->next = temp->next;
        temp->next = newNode;
        
        return;
        
        
}

int LL_length(Node* head_ref){
    Node* temp = head_ref;
    int l = 0;
    while(temp != NULL){
        ++l;
        temp = temp->next;
    }

    return l;
}

void DeleteNode_pos(Node** head_ref, int pos){
    
    Node* prev = NULL;
    Node* curr = *head_ref;
    
    if((pos >= LL_length(*head_ref)) || (pos <0) ){
        cout << "\nNode out of LL" <<endl;
        return;
    }
    
    if(pos == 0){
    
        *head_ref = (*head_ref)->next;
        delete(curr);
        return;
    
    }
    
    for(int i = 0; i < pos; i++){
        prev = curr;
        curr = curr->next;
    }
    
    prev->next = curr->next;
    delete(curr);
    return;
}


void DeleteNode(Node** head_ref, int Del_data){
    
    Node* prev = NULL;
    Node* curr = *head_ref;
    
    if(*head_ref == NULL){
        cout <<"\nDel LL is empty\n";
        return;
    }
    
    if((*head_ref)->data == Del_data){
        *head_ref = (*head_ref)->next;
        delete(curr);
        return;
    }
    
    while( (curr != NULL) && (curr->data != Del_data) ){
        prev = curr;
        curr = curr->next;
    }
    
    if(curr == NULL){
        cout << "\n Given data not in LL\n";
        return;
    }
    
    prev->next = curr->next;
    delete(curr);
    return;
}

bool search(Node* head_ref, int x){
    
    if(head_ref == NULL){
        return false;
    }
    
    if(head_ref->data == x){
        return true;
    }
    
    return search(head_ref->next,x);
    
}

void swapNodes(Node** head_ref, int x, int y){
    if(x == y){
        return;
    }
        

    Node* prevX = NULL;
    Node* currX = *head_ref;

    Node* prevY = NULL;
    Node* currY = *head_ref;

    if(*head_ref == NULL){
        cout<<"\nLL is empty\n"<<endl;
        return;
    }

    //get prev and curr nodes of x
    while(currX->data != x){
        prevX = currX;
        currX = currX->next;

    }
    //get prev and curr nodes of y
    while(currY->data != y){
        prevY = currY;
        currY = currY->next;

    }
    //if not found return
    if(currX == NULL || currY == NULL){
        return;
    }

    //if prevX is null make currY as head
    if(prevX != NULL){
        prevX->next = currY;
    }
    else{
        *head_ref = currY;
    }
    
    //if prevY is NULL make currX as head
    if(prevY != NULL){
        prevY->next = currX;
    }
    else{
        *head_ref = currX;
    }

    Node* temp = NULL;
    temp = currX->next;
    currX->next = currY->next;
    currY->next = temp;

    return;

}

int Get_nth_node(Node* head_ref,int pos){
    Node* temp = head_ref;

    for(int i=0; i<pos; i++){
        temp = temp->next;
    }

    return temp->data;
}

int Get_nth_end_node(Node* head_ref,int pos){
    Node* temp = head_ref;
    int  l = LL_length(head_ref) - pos - 1;

    for(int i=0; i<l; i++){
        temp = temp->next;
    }

    return temp->data;
}

int printMiddle(Node* head_ref){
    int l = LL_length(head_ref);
    l = l/2;
    return Get_nth_node(head_ref,l);

}


int count(Node* head_ref, int cData){
    Node* temp = head_ref;
    int count = 0;
    
    while(temp != NULL){
    
        if(temp->data == cData){
            ++count; 
        }
        
        temp = temp->next;
    }
    
    return count;
}

void Reverse(Node** head_ref){
    Node* prev = NULL;
    Node* curr = *head_ref;
    Node* Next = NULL;

    while(curr != NULL){
        
        Next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = Next;
    }

    *head_ref = prev;    
    return;
}

void ReversePrint_rec(Node* head_ref){
    
    if(head_ref == NULL){
        return;
    }
    
    ReversePrint_rec(head_ref->next);
    cout << head_ref->data << "->";
}

/*
Node* Rec_reverse(Node** head_ref){
    
    if((*head_ref)->next == NULL){
        *head_ref = p;
        return;
    }
    Rec_reverse(&(p->next);
    Node* q = p->next;
    q->next = p;
    p->next = NULL;
}
*/

Node* SortedMerge_rec(Node* a, Node* b){
    Node* result = NULL;

    if(a == NULL){
        return b;
    }

    if(b == NULL){
        return a;
    }

    if(a->data <= b->data){
        result = a;
        result->next = SortedMerge_rec(a->next,b);
    }

    if(a->data > b->data){
        result = b;
        result->next = SortedMerge_rec(a,b->next);
    }

    return result;
}

//source = 1 2 3
//dest = 4 5 6
//merge  Node 
//source = 2 3
//dest = 1 4 5 6
void MoveNode(Node** dest, Node** source){

    Node* temp = *source;
    *source = temp->next;
    temp->next = *dest;
    *dest = temp;


}

Node* sorted_merge(Node* a, Node* b){

    Node Dummy;
    Node* tail = &Dummy;
    Dummy.next = NULL;

    while(1){

        if(a == NULL){
            //cout<<"\na break"<<endl;
            tail->next = b;
            break;
        }

        else if(b == NULL){
            //cout<<"\nb break"<<endl;
            tail->next = a;
            break;
        }

        if(a->data <= b->data){
            //cout<<"\na < b "<<endl;
            MoveNode(&(tail->next),&a);
        }
        else {
            //cout<<"\na > b "<<endl;
            MoveNode(&(tail->next),&b);
        }
        tail = tail->next;



    }
    return Dummy.next;



}

void FrontBackSplit(Node* head_ref, Node** a, Node** b){
    int l = LL_length(head_ref);

    if(head_ref == NULL || head_ref->next == NULL) return;

    Node* temp = head_ref;
    Node* prev = NULL;
    for(int i = 0; i < l/2; i++){
        prev = temp;
        temp = temp->next;
    }

    prev->next = NULL;
    *b = temp;
    *a = head_ref;

}

void MergeSort(Node** head_ref){

    Node* head = *head_ref;
    

    Node* a = NULL;
    Node* b = NULL;

    if(head == NULL || head->next == NULL) return;

    FrontBackSplit(head, &a,&b);

    MergeSort(&a);
    MergeSort(&b);

    //Node* res = NULL;
    //res = sorted_merge(a,b);

    *head_ref = sorted_merge(a,b);

    


}

bool CompareLists(Node* head1, Node* head2){
    
            Node* temp1 = head1;
            Node* temp2 = head2;
    
            while(temp1 && temp2){
    
                if(temp1->data == temp2->data){
                    temp1 = temp1->next;
                    temp2 = temp2->next;
                }
                else return 0;
    
            }
    
            if(temp1 == NULL && temp2 == NULL){
                return 1;
            }
            return 0;
    
        }

   // 1->2->3->4->5->6->NULL if even fast_ptr will reach NULL 
   // 1->2->3->4->5->NULL skip mid for odd case 

bool isPalindrome(Node* head_ref){
        Node* slow_ptr = head_ref;
        Node* fast_ptr = head_ref;
        Node* prev_slow = NULL;
        Node* mid_node = NULL;
        Node* sec_half = NULL;
        bool res;

        while(fast_ptr != NULL && fast_ptr->next != NULL){

            fast_ptr = fast_ptr->next->next;
            prev_slow = slow_ptr;
            slow_ptr = slow_ptr->next;
        }

        //skip mid node for odd case. For odd case fast ptr != NULL
        //for even case slow_ptr would be NULL
        if(fast_ptr != NULL){
            mid_node = slow_ptr;
            slow_ptr = slow_ptr->next;
        }

        sec_half = slow_ptr;
        prev_slow->next = NULL;
        Reverse(&sec_half);
        
        res = CompareLists(head_ref, sec_half);

        Reverse(&sec_half);

        if(mid_node != NULL){
            prev_slow->next = mid_node;
            mid_node->next = sec_half;

        }

        return res;



    }

Node* Intersection_node(Node* head1, Node* head2){
    int L1 = LL_length(head1);
    int L2 = LL_length(head2);

    int diff = 0;
    int min = 0;

    if(L1 >= L2){
        diff = L1 - L2;
        min = L2;
    }

    else{
        diff = L2 - L1;
        min = L1;
    }
        

    Node * temp1 = head1;
    Node * temp2 = head2;

    for(int i=0; i<diff; i++){
        if(L1 > L2){
            temp1 = temp1->next;
        }
        else 
            temp2 = temp2->next;
    }

    for(int j=0; j<min; j++){
        if( (temp1 == temp2) && (temp1->data == temp2->data) ){
            return temp1;
        }

        else{
            temp1 = temp1->next;
            temp2 = temp2->next;
        }

    }


}


void DeleteDuplicates_sorted(Node* head_ref){

    
    Node* curr = head_ref;
    Node* Next = NULL;
    

    if(curr == NULL)
        return;

    while( (curr->next != NULL) ){

        

        if(curr->next->data == curr->data){
            
            
            Next = curr->next->next;
            delete(curr->next);
            curr->next = Next;
            
 
        }

        else{
            curr = curr->next;
            

        }

    }
    return;   
}

void DeleteDuplicates_unsorted(Node* head_ref){

    Node* curr = head_ref;

    
    Node* curr_d =NULL;
    Node* dup = NULL;

    while(curr != NULL && curr->next != NULL){
        
        
        curr_d = curr;


        while(curr_d->next != NULL  ){
            

                if(curr->data == curr_d->next->data){
                    dup = curr_d->next;
                    curr_d->next = curr_d->next->next;
                    delete(dup);
                    
    
                }
                else{
                    
                    
                    curr_d = curr_d->next;
                }
            
            

            
        }

        curr = curr->next;
            
    }

        
}

void swap(int* a, int* b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void pairWiseSwap(Node* head_ref){

    Node* temp = head_ref;

    while(temp != NULL && temp->next != NULL){
        swap(&temp->data , &temp->next->data);
        temp = temp->next->next;
    }

}

void MoveLastToFirst(Node** head_ref){

    if(*head_ref == NULL || (*head_ref)->next == NULL)
        return;

    Node* secLast = NULL;
    Node* Last = *head_ref;

    while(Last->next != NULL){
        secLast = Last;
        Last = Last->next;
    }

    secLast->next = NULL;
    Last->next = *head_ref;
    *head_ref = Last;

}

Node* Intersection_2_Sorted_LL(Node* A, Node* B){

    Node dummy;
    Node* tail = &dummy;

    dummy.next = NULL;

    while(A != NULL && B != NULL){
        if(A->data == B->data){
            push(&tail->next, A->data);
            tail = tail->next;
            A = A->next;
            B = B->next;
        }

        else if (A->data < B->data) /* advance the smaller list */     
            A = A->next;
        else
            B = B->next;

    }
    return dummy.next;
}

void Del_alt_nodes(Node* head_ref){
    Node* temp = head_ref;
    Node* del = NULL;
    if(head_ref == NULL)
        return;
    
    while(temp != NULL && temp->next != NULL){
        
            del = temp->next;
            temp->next = temp->next->next;
            delete(del);
            temp = temp->next;
        
    }

}




void Alt_split(Node* head_ref, Node** a, Node** b){

    Node* temp = head_ref;

    Node aDummy;
    aDummy.next = NULL;
    Node* aTail = &aDummy;

    Node bDummy;
    bDummy.next = NULL;
    Node* bTail = &bDummy;

    //cout << "\nlength " << LL_length(head_ref)<<endl;
    int l = LL_length(head_ref);
    for(int i=0; i < l; i++){

        if(i%2 == 0){
            
            append(&aTail,temp->data);
        }

        else if (i%2 != 0){
            
            append(&bTail,temp->data); 
        }
        temp = temp->next;

    }

    *a = aDummy.next;
    *b = bDummy.next;
    return;


                
    }

bool Identical_LL(Node* a, Node*b){

    Node* tempA = a;
    Node* tempB = b;

    if(LL_length(a) != LL_length(b)){
        return 0;
    }

    while(tempA != NULL && tempB != NULL){
        if(tempA->data != tempB->data){
            return 0;
        }

        tempA = tempA->next;
        tempB = tempB->next;

    }

    return 1;
}

Node* reverse_k(Node* head_ref, int k){
    Node* curr = head_ref;
    Node* prev = NULL;
    Node* Next = NULL;
    int count = 0;
    while(curr != NULL && count < k){
        Next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = Next;
        ++count;
        
    }
    if(Next != NULL)
        head_ref->next = reverse_k(Next,k);

    return prev;

}



void move_odd_to_end(Node** head_ref){
    Node* curr = *head_ref;
    Node* prev = NULL;
    Node* last = *head_ref;
    Node* temp = NULL;

    Node* odd_head = *head_ref;

    while(last->next != NULL){
        //cout<<"\nin while 1"<<endl;
        last = last->next;
    }

    while(curr->data %2 != 0 ){
        //cout<<"\nin while 2"<<endl;
        if(curr == NULL || curr->next == NULL){
            return;
        }
        
        curr = curr->next;
    }

    while(odd_head != NULL){
        if(odd_head->data %2 == 0){
            //cout<<"\nin while x if" << odd_head->data << endl;
            odd_head = odd_head->next;
        }

        else{
            //cout<<"\nin while x else" << odd_head->data << endl;
            break;
        }

    }

    while((*head_ref)->data %2 != 0){
        //cout<<"\nin while 3"<<endl;
        curr = *head_ref;
        *head_ref = curr->next;
        curr->next = NULL;
        last->next = curr;
        last = last->next;

    }
    //cout<<"\nafter while 3"<<endl;
    //printList(*head_ref);
    curr = *head_ref;

    while(curr != NULL && curr->next != NULL && last != NULL && curr->next->next != NULL){

        if(curr->next->data %2 != 0){

            
            //cout<<"\nin while 4 if"<<endl;
            //printList(*head_ref);
            temp = curr->next;
            curr->next = curr->next->next;
            last->next = temp;
            temp->next = NULL;
            last = last->next;
            if(odd_head == curr->next && odd_head->data == curr->next->data){
                break;
                //return;
            }

        }

        else{
            //cout<<"\nin while 4 else"<<endl;
            curr = curr->next;
        }

    }


}

//1->2->3->4->NULL

//4*1000 + 3*100 + 2*10 + 1*1

int LL_to_num(Node* head_ref){
    Node* temp = head_ref;

    int L = LL_length(temp);
    cout << "\nlength = " << L << endl;

    int x = 0;

    for(int n=0; n<L; n++){
        
        x = x + (temp->data)*pow(10,n);

        temp = temp->next;
    }

    return x;


}

Node* LL_plus_LL_equals_LL(int L){

    int x = 0;
    int LL = L;
    while(1){
        ++x;
        L = L/10;
        if(L < 10){
            break;
        }
    }
    x = x + 1;

    cout<<"\nnum length = " << x<<endl;
    int m = 0;
    Node* temp = NULL;
    for(int j=0; j<x; j++){
        
        m = L % 10;
        cout << "\n m = "<< m << endl;
        L = L/10;
        cout << "\n L = "<< L << endl;
        append(&temp,m);

    }

    return temp;

}






int main(){


Node* headA = NULL;
Node* headB = NULL;

Node* a = NULL;
Node* b = NULL;

/*
push(&headA,5);
push(&headA,3);
push(&headA,1);
push(&headB,6);
push(&headB,4);
push(&headB,2);

printList(headA);
printList(headB);

Node* res = NULL;
res = sorted_merge(headA,headB);

printList(res);
*/


//push(&headA,5);
push(&headA,2);
push(&headA,4);
//push(&headA,3);
push(&headA,6);
push(&headA,1);
//push(&headA,1);



Node* res = NULL;
res = LL_plus_LL_equals_LL(3456);

printList(res);





















}

