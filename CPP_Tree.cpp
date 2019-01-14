#include<iostream>
#include<limits.h>
using namespace std;
#include<queue>
#include<stack>


struct Node{
    int data;
    Node* left;
    Node* right;
};

Node* newNode(int data){
    Node* temp = new Node;
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;

}

void inorder(Node* root){
    if(root == NULL){
        return;
    }
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void inorder_iter(Node* root){
    stack<Node*> s;

    Node* curr = root;

    while(1){
        if(curr != NULL){
            s.push(curr);
            curr = curr->left;
        }

        else{
            if(s.empty() == 1){
                break;
            }

            curr = s.top();
            s.pop();
            cout << " " << curr->data;
            curr = curr->right;
        }

    }

    return;

}
/*
void in_order_iter(Node* root){
    stack<Node* > S;

    while(1){
        while(root){
            S.push(root);
            root = root->left;
        }

        if(S.empty() == 1){
            break;
        }

        root = S.front();
        cout << " " << root->data;

        S.pop();

        root = root->right;


    }
}

*/


void preorder(Node* root){
    if(root == NULL){
        return;
    }
    cout << root->data << " ";
    inorder(root->left);
    
    inorder(root->right);
}

void preorder_iter(Node* root){
    stack<Node*> s;

    if(root == NULL)
        return;
    
    Node* curr = root;
    s.push(curr);

    while(s.empty() != 1){
        curr = s.top();
        cout << " " << curr->data;
        s.pop();
        if(curr->right){
            s.push(curr->right);
        }
        if(curr->left){
            s.push(curr->left);
        }
    }

    return;


}

/*
void per_order_iter_1(Node* root){
    stack<Node* > S;

    while(1){
        while(root){
            cout << " " << root->data;
            S.push(root);
            root = root->left;
        }

        if(S.empty() == 1){
            break;
        }
        root = S.front();
        S.pop();
        root = root->right;
    }
 


}
*/
void postorder(Node* root){
    if(root == NULL){
        return;
    }
    inorder(root->left);
    
    inorder(root->right);
    cout << root->data << " ";
}

/*
void post_order_iter(Node* root){

    stack<Node* > S;

    Node* curr = root;
    while(S.empty() != 1 && curr != NULL ){

        if(curr != NULL){
            S.push(curr);
            curr = curr->left;
        }
        else{
            Node* temp = S.front()->right;

            if(temp == NULL){
                temp = S.front();
                S.pop();
                cout << " " << temp->data;

                while(S.empty() != NULL && S.front()->right == curr){
                    temp = S.front();
                    cout << " " << temp->data;
                    S.pop();
                }

            }

            else{
                curr = temp;
            }


        }


    }

}

*/

void print_level_order_queue(Node* root){
    queue<Node* > Q;
    Node* temp = root;
        Q.push(temp);
    while(temp != NULL && Q.empty() != 1){
        temp = Q.front();

        cout << " " << temp->data;
        
        if(temp->left){
            Q.push(temp->left);
        }

        if(temp->right){
            Q.push(temp->right);
        }

        Q.pop();
        

    }

}



int Max(int a, int b){
    if (a>=b)
        return a;

    else 
        return b;
}

int height(Node* root){

    int L;
    int R;
    if(root == NULL){
        return -1;
    }

    L = height(root->left);
    R = height(root->right);

    return (1 + Max(L, R) );

}

void printGivenLevel(Node* root , int L){
    if(root == NULL){
        return;
    }
    
    if(L == 1){
        cout << " " << root->data;
    }

    else if(L > 1){
        printGivenLevel(root->left, L-1);
        printGivenLevel(root->right, L-1);
    }
}

void printLevelOrder(Node* root){
    int h = height(root);
    for(int i = 1; i <= h+1; i++){
        printGivenLevel(root,i);
        cout << "\n";
    }
}

int getWidth(Node* root, int L){
    if(root == NULL)
        return 0;
    if(L == 1)
        return 1;
    
    else{
        return(getWidth(root->left,L-1) + getWidth(root->right,L-1));
    }

    
}

int GetLevelWidth(Node* root){
    int H = height(root);
    int width = 0;
    int maxWidth = 0;
    for(int i = 1; i <= H; i++){
        width = getWidth(root, i);
        cout << "\n for w = " << width;
        if(width > maxWidth){
            maxWidth = width;
        }

    }
    return maxWidth;
}

void printLevel_iter(Node* root){
    Node* temp = root;
    queue<Node*> q;

    while(temp){
        cout << temp->data << " ";
        if(temp->left){
            q.push(temp->left);
        }
        if(temp->right){
            q.push(temp->right);
        }
        temp = q.front();
        q.pop();
    }



}

Node* insert(Node* root, int data){

    Node* newNode = new Node;
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    if(root == NULL){
        root = newNode;
    } 

    else if(data < root->data){
        root->left = insert(root->left,data);
    }

    else if(data >= root->data){
        root->right = insert(root->right,data);
    }

    return root;
}

Node* FindMin(Node* root){
    Node* temp = root;
    while(temp->left != NULL){
        temp = temp->left;
    }
    return temp;
}

Node* FindMax (Node* root){
    Node* temp = root;
    while(temp->right != NULL){
        temp = temp->right;
    }
    return temp;
}

int FindMin_data(Node* root){
    Node* temp = root;
    while(temp->left != NULL){
        temp = temp->left;
    }
    return temp->data;
}

int FindMax_data(Node* root){
    Node* temp = root;
    while(temp->right != NULL){
        temp = temp->right;
    }
    return temp->data;
}

Node* Delete(Node* root, int data){
    if(root == NULL)
        return NULL;
    else if(data > root->data)
        root->right = Delete(root->right,data);
    else if(data < root->data)
        root->left = Delete(root->left,data);
    else{
        if(root->right == NULL && root->left == NULL){
            delete(root);
            root = NULL;
        }
        
        else if(root->left == NULL){
            Node* temp = root;
            root = root->right;
            delete(temp);
        }
        else if(root->right == NULL){
            Node* temp = root;
            root = root->left;
            delete(temp);
        }
        else{
            Node* temp = FindMin(root->right);
            root->data = temp->data;
            root->right = Delete(root->right,temp->data);
        }

    }
    return  root;
}

Node* LCA(Node* root, int a, int b){

    while(root != NULL){
        if(root->data > a && root->data > b){
            root = root->left;
        }

        else if(root->data < a && root->data < b){
            root = root->right;
        }

        else break;
    }
}

bool isBST(Node* root){
    if(root == NULL){
        return true;
    }

    if(root->left != NULL && FindMax_data(root->left) > root->data){
        return false;
    }


    if(root->right != NULL && FindMin_data(root->left) < root->data){
        return false;
    }

    if( !isBST(root->left) || !isBST(root->right) ){
        return false;
    }

return true;

}


int Find_max_tree(Node* root){
    int root_val,left,right;
    int max = 0;
    
    if(root != NULL){
        root_val = root->data;
        left = Find_max_tree(root->left);
        right = Find_max_tree(root->right);

        if(left > right){
            max = left;
        }

        else max = right;
        if(root_val > max){
            max = root_val;
        }

    }
    return max;
}

int Height_queue(Node* root){
    queue<Node* > Q;
    int level = -1;
    Q.push(root);
    Q.push(NULL);

    while(Q.empty() != 1){
        root = Q.front();
        Q.pop();
        if(root == NULL){
            if(Q.empty() != 1){
                Q.push(NULL);
                ++level;
            }
            
        }
        else{
            if(root->left){
                Q.push(root->left);
            }
            if(root->right){
                Q.push(root->right);
            }
        }
        
    }
    return level;
}

int Tree_leaves(Node* root){
    queue<Node* > Q;
    int count = 0;
    Q.push(root);
    Node* temp = root;
    while(Q.empty() != 1 ){
        temp = Q.front();
        Q.pop();

        if(temp->left == NULL && temp->right == NULL){
            ++count;
        }

        if(temp->left){
            Q.push(temp->left);
        }

        if(temp->right){
            Q.push(temp->right);
        }
        
    }

    return count;
}

int height_rec(Node* root){
    int Lheight = 0;
    int Rheight = 0;
    if(root == NULL){
        return 0;
    }

    Lheight = height_rec(root->left);
    Rheight = height_rec(root->right);
    return 1+max(Lheight, Rheight);
}

int search(char arr[], int start, int end, int value){
    for(int i = start; i < end; i++){
        if(arr[i] == value){
            return i;
        }
    }
}


int main(){

 Node* root = NULL;

    root = insert(root,4);
    root = insert(root,2);
    root = insert(root,3);
    root = insert(root,1);
    root = insert(root,5);
    root = insert(root,6);
    root = insert(root,7);
    
cout << "\nHello World\n";
    
    print_level_order_queue(root);
    cout << "\nHeight .." << Height_queue(root);
    cout << "\n..Tree leaves" << Tree_leaves(root);
    cout << "\n...diameter = " << height_rec(root->left) + height_rec(root->right) + 1;
    //printLevelOrder(root);
    //cout << "\nL width = " << GetLevelWidth(root);



    

}
