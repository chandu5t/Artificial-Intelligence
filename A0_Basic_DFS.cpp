#include <iostream>
#include <queue>
using namespace std;


struct node
{
    int data;
    node *left,*right;

    node(int val){
        data=val;
        left=NULL;
        right=NULL;
    }
};


node* insert(node* root,int x){

    if(root==NULL){
        return new node(x);
    }

    if(x < root->data ){
        root->left = insert(root->left,x);
    }
    else{
        root->right = insert(root->right,x);
    }

}

void Inorder(node*root){
    if(root==NULL) return ;

    Inorder(root->left);

    cout<<root->data<<" ";

    Inorder(root->right);
}


void LOT(node *root){

    if(root==NULL) return;

    queue<node*>q;
    q.push(root);

    while(!q.empty()){
        node *temp = q.front();
        q.pop();

        cout<<temp->data<<" ";

        if(temp->left != NULL)
        q.push(temp->left);

        if(temp->right != NULL)
        q.push(temp->right);
    }

    
}

int main(){

    int val;
    node *root = NULL;

    root = insert(root,8);
    insert(root,5);
    insert(root,9);

    cout<<"In-Order Traversal : " ;
    Inorder(root);


    cout<<"\n \n";

    cout<<"Level Order Traversal : ";
    LOT(root);

    cout<<endl;

}

 
