
#include <iostream>
#include <vector>

using namespace std;

class Node{
public:
    int room;
    int coins;
    Node* left;
    Node* right;

    Node(int r,int c){
        room=r;
        coins=c;
        left=NULL;
        right=NULL;
    }
};

Node* rooms[11];

void buildTree(int manager,int room,char side){
    if(side=='L') rooms[manager]->left=rooms[room];
    else rooms[manager]->right=rooms[room];
}

int countRoutes(Node* root){
    if(root==NULL) return 0;

    if(root->left==NULL && root->right==NULL) return 1;

    return countRoutes(root->left)+countRoutes(root->right);
}

void findBestRoute(Node* root,int sum,vector<int> path,int &bestSum,vector<int> &bestPath){
    if(root==NULL) return;

    sum+=root->coins;
    path.push_back(root->room);

    if(root->left==NULL && root->right==NULL){
        if(sum>bestSum){
            bestSum=sum;
            bestPath=path;
        }
        return;
    }

    findBestRoute(root->left,sum,path,bestSum,bestPath);
    findBestRoute(root->right,sum,path,bestSum,bestPath);
}

int main(){
    int coins[]={0,5,-3,4,6,2,-2,9,3,1,-1};

    for(int i=0;i<11;i++){
        rooms[i]=NULL;
    }

    for(int i=1;i<=10;i++){
        rooms[i]=new Node(i,coins[i]);
    }

    buildTree(1,2,'L');
    buildTree(1,3,'R');
    buildTree(2,4,'L');
    buildTree(2,5,'R');
    buildTree(3,6,'R');
    buildTree(5,7,'L');
    buildTree(6,8,'L');
    buildTree(6,9,'R');
    buildTree(8,10,'L');

    int routes=countRoutes(rooms[1]);

    int bestSum=-1000000;
    vector<int> bestPath;

    findBestRoute(rooms[1],0,vector<int>(),bestSum,bestPath);

    cout<<routes<<" routes"<<endl;
    cout<<"Best route: ";

    for(int i=0;i<bestPath.size();i++) cout<<bestPath[i]<<" ";

    cout<<"with "<<bestSum<<" coins"<<endl;

    return 0;
}
