#include <stdio.h>
#include <stdlib.h>

struct Node 
{
    int key ;
    struct Node *left ;
    struct Node *right;
    int height;
};
int getHeight(struct Node *n) {
    if (n==NULL)
    {
        return 0;
        return n->height;   
    }
    
}
struct Node *CreateNode(int key) {
    struct Node* node = (struct Node *) malloc(sizeof(struct Node));
    node->left = NULL ;
    node->right = NULL;
    node->height = 1;

    return node ;
}

int getBalanceFactor(struct Node *n) {
    if (n==NULL)
    {
        return 0;
    }
    return getHeight(n->left) - getHeight(n->right);
}

struct Node* leftRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* t2 = y->right;

    x->right = y;
    y->left = t2;

    y->height = max(getHeight(y->right), getHeight(y->left)) + 1;
    y->height = max(getHeight(x->right), getHeight(x->left)) + 1;

    return x;
};

struct Node* rightRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* t2 = y->left;

    x->right = y;
    y->left = t2;

    y->height = max(getHeight(y->right), getHeight(y->left)) + 1;
    y->height = max(getHeight(x->right), getHeight(x->left)) + 1;

    return x;
};