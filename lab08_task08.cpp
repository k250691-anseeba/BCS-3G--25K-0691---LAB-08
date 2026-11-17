
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

void inorder(Node* root,int arr[],int &index){
    if(root==NULL) return;

    inorder(root->left,arr,index);
    arr[index++]=root->data;
    inorder(root->right,arr,index);
}

int height(Node* root){
    if(root==NULL) return -1;

    int leftHeight=height(root->left);
    int rightHeight=height(root->right);

    return 1+(leftHeight>rightHeight?leftHeight:rightHeight);
}

bool sameShape(Node* a,Node* b){
    if(a==NULL && b==NULL) return true;
    if(a==NULL || b==NULL) return false;

    return sameShape(a->left,b->left) && sameShape(a->right,b->right);
}

void compareTrees(int a[],int nA,int b[],int nB){
    int i=0,j=0;

    cout<<"Both: ";

    while(i<nA && j<nB){
        if(a[i]==b[j]){
            cout<<a[i]<<" ";
            i++;
            j++;
        }
        else if(a[i]<b[j]){
            i++;
        }
        else{
            j++;
        }
    }

    cout<<endl;

    i=0;
    j=0;

    cout<<"Only A: ";

    while(i<nA && j<nB){
        if(a[i]==b[j]){
            i++;
            j++;
        }
        else if(a[i]<b[j]){
            cout<<a[i]<<" ";
            i++;
        }
        else{
            j++;
        }
    }

    while(i<nA) cout<<a[i++]<<" ";

    cout<<endl;

    i=0;
    j=0;

    cout<<"Only B: ";

    while(i<nA && j<nB){
        if(a[i]==b[j]){
            i++;
            j++;
        }
        else if(a[i]<b[j]){
            i++;
        }
        else{
            cout<<b[j]<<" ";
            j++;
        }
    }

    while(j<nB) cout<<b[j++]<<" ";

    cout<<endl;
}

void freeTree(Node* root){
    if(root==NULL) return;

    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

int main(){
    Node* rootA=NULL;
    Node* rootB=NULL;

    int nA,nB;
    int arrA[100],arrB[100];
    int sortedA[100],sortedB[100];

    cin>>nA;

    for(int i=0;i<nA;i++){
        cin>>arrA[i];
        rootA=insert(rootA,arrA[i]);
    }

    cin>>nB;

    for(int i=0;i<nB;i++){
        cin>>arrB[i];
        rootB=insert(rootB,arrB[i]);
    }

    int countA=0,countB=0;

    inorder(rootA,sortedA,countA);
    inorder(rootB,sortedB,countB);

    compareTrees(sortedA,countA,sortedB,countB);

    cout<<"Height A is "<<height(rootA)<<", height B is "<<height(rootB)<<endl;

    cout<<"Same shape: "<<(sameShape(rootA,rootB)?"Yes":"No")<<endl;

    freeTree(rootA);
    freeTree(rootB);

    return 0;
}
