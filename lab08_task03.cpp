
#include <iostream>

using namespace std;

class Node{
public:
    int data;
    Node* left;
    Node* right;

    Node(int value){
        data=value;
        left=NULL;
        right=NULL;
    }
};

int none=0, one=0, two=0;

Node* insert(Node* root,int value){
    if(root==NULL) return new Node(value);

    if(value<root->data) root->left=insert(root->left,value);
    else if(value>root->data) root->right=insert(root->right,value);

    return root;
}

Node* findMin(Node* root){
    while(root->left!=NULL) root=root->left;
    return root;
}

Node* removeMin(Node* root){
    if(root->left==NULL){
        Node* temp=root->right;
        delete root;
        return temp;
    }

    root->left=removeMin(root->left);
    return root;
}

Node* removeNode(Node* root,int value,bool &found){
    if(root==NULL) return NULL;

    if(value<root->data){
        root->left=removeNode(root->left,value,found);
    }
    else if(value>root->data){
        root->right=removeNode(root->right,value,found);
    }
    else{
        found=true;

        if(root->left==NULL && root->right==NULL){
            cout<<value<<" no sub-branch"<<endl;
            none++;
            delete root;
            return NULL;
        }
        else if(root->left==NULL || root->right==NULL){
            cout<<value<<" one sub-branch"<<endl;
            one++;
            Node* temp=(root->left!=NULL)?root->left:root->right;
            delete root;
            return temp;
        }
        else{
            Node* temp=findMin(root->right);
            int successor=temp->data;
            cout<<value<<" two sub-branches, replaced by "<<successor<<endl;
            two++;
            root->data=successor;
            root->right=removeMin(root->right);
        }
    }

    return root;
}

void preorder(Node* root){
    if(root==NULL) return;

    cout<<root->data<<" ";
    preorder(root->left);
    preorder(root->right);
}

int height(Node* root){
    if(root==NULL) return -1;

    int leftHeight=height(root->left);
    int rightHeight=height(root->right);

    return 1+max(leftHeight,rightHeight);
}

void freeTree(Node* root){
    if(root==NULL) return;

    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

int main(){
    Node* root=NULL;
    int n,m;

    cin>>n;

    int values[100];

    for(int i=0;i<n;i++){
        cin>>values[i];
        root=insert(root,values[i]);
    }

    cin>>m;

    int removals[100];

    for(int i=0;i<m;i++){
        cin>>removals[i];
    }

    for(int i=0;i<m;i++){
        bool found=false;
        root=removeNode(root,removals[i],found);

        if(!found) cout<<removals[i]<<" Code not found"<<endl;
    }

    cout<<"Remaining: ";
    preorder(root);
    cout<<endl;

    cout<<"Height "<<height(root)<<endl;
    cout<<"Kinds: none "<<none<<", one "<<one<<", two "<<two<<endl;

    freeTree(root);

    return 0;
}
