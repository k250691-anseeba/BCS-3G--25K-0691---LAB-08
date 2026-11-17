
#include <iostream>
#include <queue>

using namespace std;

class Node{
public:
    int data;
    Node* left;
    Node* right;
    Node* parent;

    Node(int value){
        data=value;
        left=NULL;
        right=NULL;
        parent=NULL;
    }
};

Node* nodes[1001];

void initialize(){
    for(int i=0;i<=1000;i++) nodes[i]=NULL;
}

void buildTree(int parent,int child,char side){
    if(nodes[parent]==NULL) nodes[parent]=new Node(parent);
    if(nodes[child]==NULL) nodes[child]=new Node(child);

    if(side=='L') nodes[parent]->left=nodes[child];
    else nodes[parent]->right=nodes[child];

    nodes[child]->parent=nodes[parent];
}

Node* findRoot(){
    for(int i=0;i<=1000;i++){
        if(nodes[i]!=NULL && nodes[i]->parent==NULL) return nodes[i];
    }

    return NULL;
}

bool checkFull(Node* root){
    if(root==NULL) return true;

    if((root->left==NULL && root->right!=NULL) || (root->left!=NULL && root->right==NULL)) return false;

    return checkFull(root->left) && checkFull(root->right);
}

bool checkNeat(Node* root){
    if(root==NULL) return true;

    queue<Node*> q;
    q.push(root);

    bool gap=false;

    while(!q.empty()){
        Node* current=q.front();
        q.pop();

        if(current==NULL){
            gap=true;
        }
        else{
            if(gap) return false;

            q.push(current->left);
            q.push(current->right);
        }
    }

    return true;
}

void printFreePass(Node* root){
    if(root==NULL) return;

    queue<Node*> q;
    q.push(root);

    bool found=false;

    cout<<"free pass ";

    while(!q.empty()){
        Node* current=q.front();
        q.pop();

        if((current->left==NULL && current->right!=NULL) || (current->left!=NULL && current->right==NULL)){
            cout<<current->data<<" ";
            found=true;
        }

        if(current->left!=NULL) q.push(current->left);
        if(current->right!=NULL) q.push(current->right);
    }

    if(!found) cout<<"None";

    cout<<endl;
}

int main(){
    char names[]={'B','C','D'};

    for(int t=0;t<3;t++){
        initialize();

        int n;
        cin>>n;

        for(int i=0;i<n;i++){
            int parent,child;
            char side;

            cin>>parent>>child>>side;
            buildTree(parent,child,side);
        }

        Node* root=findRoot();

        cout<<names[t]<<": Full "<<(checkFull(root)?"Yes":"No")<<", Neat "<<(checkNeat(root)?"Yes":"No")<<", ";

        printFreePass(root);
    }

    return 0;
}
