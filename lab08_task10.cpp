
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

Node* insert(Node* root,int value){
    if(root==NULL) return new Node(value);

    if(value<root->data) root->left=insert(root->left,value);
    else if(value>root->data) root->right=insert(root->right,value);

    return root;
}

bool search(Node* root,int value){
    if(root==NULL) return false;

    if(root->data==value) return true;

    if(value<root->data) return search(root->left,value);

    return search(root->right,value);
}

Node* findBoss(Node* root,int a,int b){
    if(root==NULL) return NULL;

    if(a<root->data && b<root->data) return findBoss(root->left,a,b);

    if(a>root->data && b>root->data) return findBoss(root->right,a,b);

    return root;
}

int findDistance(Node* root,int value){
    int distance=0;

    while(root!=NULL && root->data!=value){
        distance++;

        if(value<root->data) root=root->left;
        else root=root->right;
    }

    return distance;
}

void checkEmployees(Node* root,int a,int b){
    if(!search(root,a) || !search(root,b)){
        cout<<"Employee not found"<<endl;
        return;
    }

    Node* boss=findBoss(root,a,b);

    int distanceA=findDistance(boss,a);
    int distanceB=findDistance(boss,b);

    cout<<"("<<a<<", "<<b<<"): boss "<<boss->data<<", distance "<<distanceA+distanceB<<endl;
}

void freeTree(Node* root){
    if(root==NULL) return;

    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

int main(){
    Node* root=NULL;

    int n;
    cin>>n;

    for(int i=0;i<n;i++){
        int value;
        cin>>value;
        root=insert(root,value);
    }

    int a,b;

int q;
cin>>q;

for(int i=0;i<q;i++){
    int a,b;
    cin>>a>>b;
    checkEmployees(root,a,b);
}
    freeTree(root);

    return 0;
}
