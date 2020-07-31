#include<iostream>
using namespace std;

class HAVL{
    public:
      struct node{
      node* left;
      node* right;
      node* parent;
      int data;
      node(int data):data(data),left(nullptr),right(nullptr),parent(nullptr){}
  } ; 
    node* root;
    HAVL():root(nullptr){}
    node* add(int ele){insertBST(root,new node(ele)); return root;}
    node* getRoot() { return root;}
    void printTree(node *root);
 
  bool insertBST(node *&root, node *t);

};
void HAVL::printTree(node *root)
{
    if(root == NULL)
        return;
    printTree(root->left);
    cout<<root->data<<" -> ";
    printTree(root->right);
}
bool HAVL::insertBST(node *&root, node *t)
{
    if(root == NULL)
    {
        root = t;
        return true;
    }
    node *p = root,*g = nullptr;
    while(p != nullptr)
    {
        g = p;
        if(p->data == t->data)
        {
            return false;
        }
        if(p->data > t->data)
        {
            p = p->left;
        }
        else
        {
            p = p->right;
        }
    }
    if(g->data > t->data)
        g->left = t;
    else
        g->right = t;
        
    return true;
}
