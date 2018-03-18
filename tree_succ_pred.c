#include<stdio.h>
#include<stdlib.h>

struct Node{
    int data;
    struct Node* left;
    struct Node* right;

};

struct Node* newNode(int data){
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}


struct Node* insert(struct Node* root,int data){

    if(root == NULL){
        root = newNode(data);
    }

    else if(data < root->data){
        root->left = insert(root->left,data);
    }

    else if(data >= root->data){
        root->right = insert(root->right,data);
    }

    return root;
}

struct Node* minValNode(struct Node* node){
    struct Node* curr = node;

    while(curr->left != NULL){
        curr = curr->left;
    }

    return curr;
}

struct Node* Delete_Node(struct Node* root, int key){
    if(root == NULL){
        return root;
    }

    if(key < root->data){
        root->left = Delete_Node(root->left,key);
    }

    else if(key > root->data){
        root->right = Delete_Node(root->right,key);
    }

    else{

        if(root->left == NULL){
            struct Node* temp = root->right;
            free(root);
            return temp;
        }

        else if(root->right == NULL){
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* temp = minValNode(root->right);

        root->data = temp->data;

        root->right = Delete_Node(root->right,temp->data);


    }
}

void inorder_succ_pred(struct Node* root, int key,struct Node** pred, struct Node** succ){
    //struct Node* succ;
    //struct Node* pred;
    if(root == NULL) return;

    if(root->data == key){

        if(root->left != NULL){
            struct Node* temp = root->left;
            while(temp->right){
                temp = temp->right;
            }
            *pred = temp;
        }

        if(root->right != NULL){
            struct Node* temp = root->right;
            while(temp->left){
                temp = temp->left;
            }
            *succ = temp;
        }
        return;
    }

    if(key > root->data){
        *pred = root;
        inorder_succ_pred(root->right,key,pred,succ);
    }

    else{
        *succ = root;
        inorder_succ_pred(root->left,key,pred,succ);
    }
}

void inorder_rec(struct Node* root){
    if(root == NULL){
        return;
    }

    inorder_rec(root->left);
    printf("%d ",root->data);
    inorder_rec(root->right);
}

void preorder_rec(struct Node* root){
    if(root == NULL){
        return;
    }
    printf("%d ",root->data);
    preorder_rec(root->left);
    preorder_rec(root->right);
}

void postorder_rec(struct Node* root){
    if(root == NULL){
        return;
    }
    postorder_rec(root->left);
    postorder_rec(root->right); 
    printf("%d ",root->data);  
}



int main(){

    struct Node* root = NULL;
    root = insert(root,4);
    root = insert(root,1);
    root = insert(root,2);
    root = insert(root,3);
    root = insert(root,5);
    root = insert(root,6);

    inorder_rec(root);

    struct Node* succ = NULL;
    struct Node* pred = NULL;

    inorder_succ_pred(root,3,&pred,&succ);
    printf("\nSucc = %d",succ->data);
    printf("\nPred = %d",pred->data);
    return 0;
}
