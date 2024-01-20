#include <cstdlib>
#include <ctime>
#include "demo.h"

#define N 10000000

using namespace std;

Node *addToTree(Tree *root,int value){
  Node *pN = new Node(value);
  
  root->leaf = root->insertLeaf(root,root->leaf,pN);

  pN = root->searchNode(root,root->leaf,value);

  return root->searchNode(root,root->leaf,value);;
}

Node *reBalance(Tree* root,Node *pN,int value){

  while(pN->parent !=root->NIL){
    pN = root->arrangeNode(root,pN,value);

    if(pN->parent!=root->NIL){
      if( (pN->parent)->data> pN->data ){
        (pN->parent)->left = pN;
      }
      else if( (pN->parent)->data < pN->data ){
        (pN->parent)->right = pN;
      }
      pN = pN->parent;
    }

  }

  return pN;
}

void insertToTree(Tree *root,int value){

  Node *pN;
  pN = addToTree(root,value);
  
  if(pN->parent!=root->NIL)
    root->leaf = reBalance(root,pN->parent,value);
}

int main(){

  Tree *root = new Tree();
  
  srand(unsigned(time(0)));
  
  const int MAX = N;
  const int MIN = 1;

  int a = 0;
  for(int i=0;i<MAX;i++){
    a = (rand()%(MAX-MIN+1) +MIN);
    insertToTree(root,a);
  }

  Node *pD;
  a = 0;
  
  for(int i=1;i<MAX;i++){
    a = (rand()%(MAX-MIN+1) +MIN);
    pD =root->searchNode(root,root->leaf,a);
  
      if(pD->data ==a){
        
        root->deleteNode(root, pD);
      }
  }
  
  return 1;
}
