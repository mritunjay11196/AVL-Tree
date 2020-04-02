#ifndef avl_h
#define avl_h


struct Node
{
    Node* lchild;
    int data;
    int height;
    Node* rchild;
}*root = nullptr;

int nodeHeight(Node* p)
{
    int hLeft, hRight;
    hLeft = p && p->lchild ? p->lchild->height : 0;
    hRight = p && p->rchild ? p->rchild->height : 0;
    
    return hLeft>hRight ? hLeft + 1 : hRight + 1;
}

Node* llRotation(Node* p)
{
    Node* pL = p->lchild;
    Node* pLR = pL->rchild;
    
    pL->rchild = p;
    p->lchild = pLR;
    p->height = nodeHeight(p);
    pL->height = nodeHeight(pL);
    
if(root == p)                           // 'p' was the old root
        root = pL;
    return pL;                          // 'pL' is the new root
}

Node* lrRotation(Node* p)
{
    Node* pL = p->lchild;
    Node* pLR = pL->rchild;
    
    pL->rchild = pLR->lchild;
    p->lchild = pLR->rchild;
    
    pLR->lchild = pL;
    pLR->rchild = p;
    
    pL->height = nodeHeight(pL);
    p->height = nodeHeight(p);
    pLR->height = nodeHeight(pLR);
    
    
    if(root == p)                           // 'p' is the old root
        root = pLR;
    return pLR;                              // 'pLR' is the new root
}

Node* rrRotation(Node* p)
{
    return 0;
}

Node* rlRotation(Node* p)
{
    return 0;
}

int balanceFactor(Node* p)
{
    int hLeft = p && p->lchild ? p->lchild->height : 0;
    int hRight = p && p->rchild ? p->rchild->height : 0;
    
    return hLeft - hRight;
}

Node* recursiveInsert(Node* p, int key)             // p is root node
{
   Node *t=NULL;
    if(p==NULL)
    {
        t = new Node;                               // new node
        t->data = key;
        t->height = 1;                              // we are starting height with 1 rather than 0
        t->lchild = t->rchild=NULL;
        return t;
    }
    
    if(key < p->data)
        p->lchild = recursiveInsert(p->lchild,key);
    else if(key > p->data)
        p->rchild = recursiveInsert(p->rchild,key);
    
    p->height = nodeHeight(p);
    
    if(balanceFactor(p) == 2 && balanceFactor(p->lchild) == 1)
        return llRotation(p);
    else if(balanceFactor(p) == 2 && balanceFactor(p->lchild) == -1)
        return lrRotation(p);
    else if(balanceFactor(p) == -2 && balanceFactor(p->lchild) == -1)
        return rrRotation(p);
    else if(balanceFactor(p) == -2 && balanceFactor(p->lchild) == 1)
        return rlRotation(p);
    
    return p;
}


#endif
