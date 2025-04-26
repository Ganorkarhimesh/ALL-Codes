#include <stdio.h>
#include <stdlib.h>
struct node 
{
    struct node *child ;
    int data ;
    struct node *rchild ;
};
struct node*getnode(int val) 
{
    struct node *p = NULL;
    p = (struct node *) malloc(sizeof(struct node));
    p->data = val ;
    p->child = NULL ;
    p->rchild = NULL ;
    return (p);
};
void Inorder(struct node *root)
{
    if (root!=NULL)
    {
        Inorder(root->child);
        printf("%d",root->data);
        Inorder(root->rchild);
    }
    
}
void postorder(struct node *root) {
    if (root != NULL)
    {
        postorder(root->child);
        postorder(root->rchild);
        printf("%d",root->data);
    }
    
}
int main() 
{
    struct node *root;
    root = getnode(10);
    root -> child = getnode(10);
    root -> rchild->child = getnode(40);
    root->rchild = getnode(30);
    root->rchild->rchild = getnode(50);
    Inorder(root);
    postorder(root);
    return 0;
}