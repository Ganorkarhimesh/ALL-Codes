#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};

int getHeight(struct Node *n) {
    if (n == NULL) {
        return 0;
    }
    return n->height;
}

struct Node *CreateNode(int key) {
    struct Node* node = (struct Node *) malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int getBalanceFactor(struct Node *n) {
    if (n == NULL) {
        return 0;
    }
    return getHeight(n->left) - getHeight(n->right);
}

struct Node* leftRotate(struct Node* y) {
    struct Node* x = y->right;
    struct Node* t2 = x->left;

    x->left = y;
    y->right = t2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

struct Node* rightRotate(struct Node* x) {
    struct Node* y = x->left;
    struct Node* t2 = y->right;

    y->right = x;
    x->left = t2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

struct Node *insert(struct Node* node, int key) {
    if (node == NULL) {
        return CreateNode(key);
    }

    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        return node;
    }

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int bf = getBalanceFactor(node);

    if (bf > 1 && key < node->left->key) {
        return rightRotate(node);
    }
    if (bf < -1 && key > node->right->key) {
        return leftRotate(node);
    }
    if (bf > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (bf < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

void preOrder(struct Node *root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main() {
    struct Node *root = NULL;
    root = insert(root, 1);
    root = insert(root, 2);
    root = insert(root, 3);
    root = insert(root, 4);
    root = insert(root, 5);

    preOrder(root);
    printf("\n");

    return 0;
}
