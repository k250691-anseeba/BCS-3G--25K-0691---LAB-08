
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

void rangeSearch(Node* root,int low,int high,int &count,int &looked){
    if(root==NULL) return;

    looked++;

    if(root->data>low) rangeSearch(root->left,low,high,count,looked);

    if(root->data>=low && root->data<=high){
        cout<<root->data<<" ";
        count++;
    }

    if(root->data<high) rangeSearch(root->right,low,high,count,looked);
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

    int values[100];

    for(int i=0;i<n;i++){
        cin>>values[i];
        root=insert(root,values[i]);
    }

    int low,high;
    cin>>low>>high;

    int count=0;
    int looked=0;

    cout<<"For range "<<low<<" to "<<high<<": ";

    rangeSearch(root,low,high,count,looked);

    if(count==0) cout<<"No amounts";

    cout<<endl;
    cout<<"Count: "<<count<<endl;
    cout<<"Looked at "<<looked<<" of "<<n<<" nodes"<<endl;

    freeTree(root);

    return 0;
}
