#include<iostream>
using namespace std;

class Node{
    public:
    Node* right;
    Node* left;
    int data;
    Node(int val){
        right=left = NULL;
        data = val;
    }
};

class Tree{
    public:
    Node* root;
    Tree(){
        root = NULL;
    }

    Node* insertinTREE(int val, Node* r){
        if(r==NULL){
            return new Node(val);
        }
        if(val<r->data){
            r->left = insertinTREE(val,r->left);
        }
        else if(r->data<val){
            r->right = insertinTREE(val,r->right);
        }

        return r;
    }

    bool search(Node* r, int target, int&cmp, int &smaller, int &bigger){
        if(r== NULL){
            cout<<target<<": NOT FOUND, "<<cmp<<" compared ";
            cout<<"smaller ";
            if(smaller==-1){
                cout<<"none,";
            }
            else
            cout<<smaller;

            cout<<" bigger ";
            if(bigger==-1){
                cout<<"none "<<endl;
            }
            else 
            cout<<bigger<<endl;


            return false;
        }
        cmp++;
        if(r->data == target){
            cout<<r->data<<": FOUND, "<<cmp<<" compared"<<endl;
            return true;
        }
        if(r->data>target){
            bigger= r->data;
            return search(r->left, target, cmp,smaller,bigger );
        }
        else{
            smaller = r->data;
            return search(r->right,target,cmp,smaller,bigger);
        }
    }
};

int main(){

    Tree t1;
    int input[] = {45 ,20 ,60 ,10 ,30 ,50 ,70 ,25, 35};
    for(int val:input){
        t1.root = t1.insertinTREE(val, t1.root);
    }

int queries[] = {35, 55, 5, 70};

for(int i = 0; i < 4; i++){
    int cmp = 0;
    int smaller = -1;
    int bigger = -1;

    t1.search(t1.root, queries[i], cmp, smaller, bigger);
}

    return 0;
}