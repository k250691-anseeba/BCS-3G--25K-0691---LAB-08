#include<iostream>
using namespace std;

class Node{
    public:
    Node* right;
    Node* left;
    int data;

    Node(int val){
        data = val;
        left=right=NULL;
    }
};

class Tree{
    public:
    Node* root;
    Tree(){
        root=NULL;
    }
    Node* insertTokenInTree(int val, Node*r){
        if(r==NULL){
            return new Node(val);
        }

        if(val<r->data){
            r->left= insertTokenInTree(val,r->left);
        }
        else if(val>r->data){
            r->right = insertTokenInTree(val,r->right);
        }
        else{
            cout<<"Token already issued: "<<val<<endl;
        }

        return r;
    }

    void docCallingList(Node* r){ //inorder
        if(r==NULL){
            return; 
        }
        docCallingList(r->left);
        cout<<r->data<<" ";
        docCallingList(r->right);
    }

    void generateBackupList(Node* r, int arr[], int &i){
        if(r==NULL){
            return;
        }
        arr[i] = r->data;
        i++;
        generateBackupList(r->left, arr,i);
        generateBackupList(r->right, arr,i);        
    }

    bool identical(Node* r1, Node* r2){
        if(r1==NULL && r2==NULL){
            return true;
        }
        if(r1 == NULL || r2 == NULL){
            return false;
        }
        if(r1->data != r2->data){
            return false;
        }
        return identical(r1->left, r2->left)&&identical(r1->right, r2->right);
    }
};

int main(){
    //input: 50 30 70 20 40 60 80 30 65
    int n;
    int val;
    Tree t1;
    cout<<"Enter number of tokens to insert: ";
    cin>>n;
    cout<<"Enter tokens: "<<endl;
    for(int i=0; i<n; i++){
        cin>>val;
        t1.root = t1.insertTokenInTree(val, t1.root);
    }


    cout<<"Calling List: ";
    t1.docCallingList(t1.root);
    cout<<endl;

    //backup list from t1
    int backuplist[n];
    int x = 0;
    t1.generateBackupList(t1.root,backuplist,x);

    cout<<"Backup List: ";
    for(int i = 0; i<x; i++){
        cout<<backuplist[i]<<" ";
    }
    cout<<endl;

    Tree t2;
    for(int i = 0; i<x; i++){
        t2.root = t2.insertTokenInTree(backuplist[i], t2.root);
    }

    cout<<"Comparing: "<<endl;
    if(t1.identical(t1.root, t2.root)){
        cout<<"Backup is safe"<<endl;
    }
    else{
        cout<<"Backup is not safe"<<endl;
    }

    return 0;
}