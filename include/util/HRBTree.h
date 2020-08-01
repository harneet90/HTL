#include<iostream>
#include<cstdlib>
using namespace std;
template<typename T>
class HAVL{
    private:
      struct node{
      node* left;
      node* right;
      node* parent;
      const T* data;
      long hb;
      node(const T& data):data(new T(data)),left(nullptr),right(nullptr),parent(nullptr),hb(0){}
  } ; 
    node* root;
    void _printTree(node *root);
    bool _lookup(const T &ele, node* root,  node *&parent);
    void _rotateLeftLeft(node* root);
    void _rotateLeftRight(node* root);
    void _rotateRightLeft(node* root);
    void _rotateRightRight(node* root);
    bool _insert(node *&root, node *t, node *&imb);
    int _balance(node* root);
    public:
    HAVL():root(nullptr){}
    void add(const T &ele);
    bool lookup(const T &ele){node *parent; return _lookup(ele,root,parent);}
    void remove(const T &ele);
    void printTree(){_printTree(root);}
};
template<typename T>
int HAVL<T>::_balance(node* root)
{
    if(root == nullptr)
        return 0;
    int left = _balance(root->left);
    int right = _balance(root->right);
    if(abs(left-right) > 1)
    {
        if(left > right)
        {
            if(root->left->hb == -1)
                _rotateLeftLeft(root);
            else
                _rotateLeftRight(root);
        }
        else
        {
            if(root->right->hb == -1)
                _rotateRightLeft(root);
            else
            {
                _rotateRightRight(root);
            }
        }
        left = _balance(root->left);
        right = _balance(root->right);
    }
    return max(left,right) + 1;
}
template<typename T>
void HAVL<T>::add(const T &ele)
{
    node *imb;
    _insert(root, new node(ele), imb);
    _balance(root);
    cout<<*(root->data)<<" ";
}
template<typename T>
void HAVL<T>::_rotateRightRight(node* root)
{
    
    node *parent = root->parent; 
    node *temp = root->right;
    root->right = temp->left; if(temp->left) temp->left->parent = root;
    temp->left = root; root->parent = temp;
    if(parent)
    {
        if(parent->right == root)
            parent->right = temp;
        else
            parent->left = temp;
    }
    else
    {
        this->root = temp;
    }
    temp->parent = parent;
}
template<typename T>
void HAVL<T>::_rotateLeftLeft(node* root)
{
    node *parent = root->parent;
    node *temp = root->left;
    root->left = temp->right; if(temp->right) temp->right->parent = root;
    temp->right = root; root->parent = temp;
    if(parent)
    {
        if(parent->right == root)
            parent->right = temp;
        else
            parent->left = temp;
    }
    else
    {
        this->root = temp;
    }
    temp->parent = parent;
}
template<typename T>
void HAVL<T>::_rotateLeftRight(node* root)
{
    node *parent = root->parent;
    node *temp = root->left;
    root->left = temp->right; temp->right->parent = root;
    temp->right = root->left->left; if(temp->right) temp->right->parent=temp;
    root->left->left = temp; temp->parent = root->left;
    _rotateLeftLeft(root);
}
template<typename T>
void HAVL<T>::_rotateRightLeft(node* root)
{
    node *parent = root->parent;
    node *temp = root->right;
    root->right = temp->left; temp->left->parent = root;
    temp->left = root->right->right; if(temp->left) temp->left->parent=temp;
    root->right->right = temp; temp->parent = root->right;
    _rotateRightRight(root);
}
template<typename T>
bool HAVL<T>::_lookup(const T &ele, node* root,  node *&parent)
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
bool HAVL<T>::_insert(node *&root, node *t, node *&imb)
{
    bool lastLeft;
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
        if(*(t->data) < *(p->data))
        {
            p->hb--;
            p = p->left;
        }
        else
        {
            p->hb++;
            p = p->right;
        }
        if(abs(g->hb) > 1)
        {
            imb = g;
        }
    }
    if(*(g->data) > *(t->data))
        g->left = t;
    else
        g->right = t;
    
    t->parent = g;
    return true;
}
