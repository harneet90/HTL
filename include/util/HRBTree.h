#include<iostream>
using namespace std;
template<typename T>
class HAVL{
    private:
      struct node{
      node* left;
      node* right;
      node* parent;
      const T* data;
      node(const T& data):data(new T(data)),left(nullptr),right(nullptr),parent(nullptr){}
  } ; 
    node* root;
    void _printTree(node *root);
    bool _lookup(const T &ele, node* root,  node *&parent)
    {
        if(root == nullptr)
            return false;
        if(*(root->data) == ele)
        {
            return true;
        }
        if(*(root->data) < ele)
        {
            if(root->right)
            {
                if(*(root->right->data) == ele)
                {
                    parent = root;
                    return true;
                }
                else
                {
                    return _lookup(ele, root->right, parent);
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            if(root->left) 
            {
                if(*(root->left->data) == ele)
                {
                    parent = root;
                    return true;
                }
                else
                {
                    return _lookup(ele, root->left, parent);
                }
            }
            else
            {
                return false;
            }
        }   
    }
    public:
    HAVL():root(nullptr){}
    node* add(const T &ele){insertBST(root,new node(ele)); return root;}
    bool lookup(const T &ele){node *parent; return _lookup(ele,root,parent);}
    void remove(const T &ele);
    void printTree(){_printTree(root);}
    
  bool insertBST(node *&root, node *t);

};
template<typename T>
void HAVL<T>::remove(const T &ele)
{
    node *parent = NULL;
    if(_lookup(ele,root,parent))
    {
        node *N = root, *temp = NULL;
        bool left = false;
        if(parent)
        {
            if(parent->left  && ele == *(parent->left->data))
            {
                N = parent->left;
                left = true;
            }
            else
            {
                N = parent->right;
            }
        }
        if(!N->left)
        {
            temp = N->right;
        }
        else if(!N->right)
        {
            temp = N->left;
        }
        else
        {
            node *t1, *t2;
            t1 = N;
            t2 = t1->right;
            if(t2->left != nullptr)
            {
                while(t2->left != nullptr)
                {
                    t1 = t2;
                    t2 = t2->left;
                }
                t1->left = t2->right;
                t2->right = N->right;
            }
            t2->left = N->left;
            temp = t2;
        }
        if(parent)
        {
            if(left)
            {
                parent->left = temp;
            }
            else
            {
                parent->right = temp;
            }
        }
        else
        {
            root = temp;
        }
        delete N;
    }
}
template<typename T>
void HAVL<T>::_printTree(node *root)
{
    if(root == NULL)
        return;
    _printTree(root->left);
    cout<<*(root->data)<<" -> ";
    _printTree(root->right);
}
template<typename T>
bool HAVL<T>::insertBST(node *&root, node *t)
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
        if(*(p->data) == *(t->data))
        {
            return false;
        }
        if(*(p->data) > *(t->data))
        {
            p = p->left;
        }
        else
        {
            p = p->right;
        }
    }
    if(*(g->data) > *(t->data))
        g->left = t;
    else
        g->right = t;
        
    return true;
}
