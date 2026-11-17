
#include <iostream>

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

bool checkTree(Node* root,long long low,long long high,Node* lowNode,Node* highNode,int &wrong,int &ancestor){
    if(root==NULL) return true;

    if(root->data<=low){
        wrong=root->data;
        ancestor=lowNode->data;
        return false;
    }

    if(root->data>=high){
        wrong=root->data;
        ancestor=highNode->data;
        return false;
    }

    if(!checkTree(root->left,low,root->data,lowNode,root,wrong,ancestor)) return false;

    if(!checkTree(root->right,root->data,high,root,highNode,wrong,ancestor)) return false;

    return true;
}

int main(){
    int n;

    for(int t=1;t<=2;t++){
        initialize();

        cin>>n;

        for(int i=0;i<n;i++){
            int parent,child;
            char side;

            cin>>parent>>child>>side;
            buildTree(parent,child,side);
        }

        Node* root=findRoot();

        int wrong=0,ancestor=0;

        bool valid=checkTree(root,-1000000000LL,1000000000LL,NULL,NULL,wrong,ancestor);

        cout<<"Tree "<<t<<": ";

        if(valid){
            cout<<"Valid"<<endl;
        }
        else{
            cout<<"Invalid, first wrong ID "<<wrong<<", it disagrees with "<<ancestor<<endl;
        }
    }

    return 0;
}
