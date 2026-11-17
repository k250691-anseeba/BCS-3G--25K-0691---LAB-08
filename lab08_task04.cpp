
#include <iostream>
#include <queue>
#include <vector>

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

Node* employees[101];

void buildTree(int manager,int employee,char side){
    if(employees[manager]==NULL) employees[manager]=new Node(manager);
    if(employees[employee]==NULL) employees[employee]=new Node(employee);

    if(side=='L') employees[manager]->left=employees[employee];
    else employees[manager]->right=employees[employee];

    employees[employee]->parent=employees[manager];
}

void printLevels(Node* root){
    if(root==NULL) return;

    queue<Node*> q;
    q.push(root);

    int level=0;

    while(!q.empty()){
        int count=q.size();

        cout<<"Level "<<level<<": ";

        for(int i=0;i<count;i++){
            Node* current=q.front();
            q.pop();

            cout<<current->data<<" ";

            if(current->left!=NULL) q.push(current->left);
            if(current->right!=NULL) q.push(current->right);
        }

        cout<<endl;
        level++;
    }

    cout<<"Height "<<level-1<<endl;
}

void printNoReports(Node* root){
    if(root==NULL) return;

    queue<Node*> q;
    q.push(root);

    cout<<"No one under them: ";

    while(!q.empty()){
        Node* current=q.front();
        q.pop();

        if(current->left==NULL && current->right==NULL) cout<<current->data<<" ";

        if(current->left!=NULL) q.push(current->left);
        if(current->right!=NULL) q.push(current->right);
    }

    cout<<endl;
}

void printChain(int employee){
    if(employees[employee]==NULL){
        cout<<"Employee not found"<<endl;
        return;
    }

    vector<int> chain;
    Node* current=employees[employee];

    while(current!=NULL){
        chain.push_back(current->data);
        current=current->parent;
    }

    cout<<"For "<<employee<<": chain ";

    for(int i=chain.size()-1;i>=0;i--) cout<<chain[i]<<" ";

    Node* person=employees[employee];
    Node* parent=person->parent;

    cout<<", colleague ";

    if(parent==NULL){
        cout<<"None";
    }
    else if(parent->left==person && parent->right!=NULL){
        cout<<parent->right->data;
    }
    else if(parent->right==person && parent->left!=NULL){
        cout<<parent->left->data;
    }
    else{
        cout<<"None";
    }

    cout<<endl;
}

int main(){
    for(int i=0;i<101;i++) employees[i]=NULL;

    employees[1]=new Node(1);

    int n;
    cin>>n;

    for(int i=0;i<n;i++){
        int manager,employee;
        char side;

        cin>>manager>>employee>>side;
        buildTree(manager,employee,side);
    }

    printLevels(employees[1]);
    printNoReports(employees[1]);

    int a,b;
    cin>>a>>b;

    printChain(a);
    printChain(b);

    return 0;
}
