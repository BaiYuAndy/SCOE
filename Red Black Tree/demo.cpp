#include "demo.h"
#include <cstdlib>
#include <ctime>

#define N 10000000

using namespace std;

int main(){

  RBT *root = new RBT();

  Node *pN;
  for(int i=1;i<N;i++){
    pN = new Node(i);

    root = root->insertNode(root,pN);
  }

  Node *pD;// = root->searchNode(root,root->root,88);
  for(int i=1;i<N-1;i++){
    pD =root->searchNode(root,root->root,i);
    
    if(pD!=NULL)
      root->rb_delete(root, pD);
    
  }

  //root->rb_delete(root, pD);
  root->preOrder(root, root->root);
  cout<<"\n";
  root->inOrder(root, root->root);

}