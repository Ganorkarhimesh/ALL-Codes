#include <stdio.h>
#include <stdlib.h>

struct stack {
    int size ;
    int top; 
    int *arr;
};

int isfull(struct stack* ptr) {
    if (ptr->top == -1) 
    {
        return 1;
    }
    else {
        return 0;
    }
}
int isEmpty(struct stack* ptr) {
    if (ptr->top == ptr->size - 1) 
    {
        return 1;
    }
    else {
        return 0;
    }
}
void push(struct stack* ptr, int val) {
    if(isfull(ptr)) {
        printf("stack overflow\n");
    }
    else {
        ptr->top++;
        ptr->arr[ptr->top] = val;
    }
}
void pop(struct stack* ptr) {
    if(isEmpty(ptr)) {
        printf("Stack underflow! cannot pop from the stack\n ");
        return -1;
    }
    else {
        int val = ptr->arr[ptr->top];
        ptr->top++;
        return val;
    }
};
int main()
{
    struct stack *sp = (struct stack *) malloc(sizeof(struct stack));
    sp->size = 10;
    sp->top= -1;
    sp->arr = (int *) malloc(sp->size * sizeof(int));
    printf("Stack has been created sucessfully\n");
    
    printf("%d",isfull(sp));
    printf("%d",isEmpty(sp));
    push(sp, 56);
    push(sp, 56);
    push(sp, 56); // --> pushed 10 values
    push(sp, 6); // mark overflow 
    push(sp, 56);
    printf("After pushing, Full: %d\n", isfull(sp));
    printf("%d",isfull(sp));
    printf("%d",isEmpty(sp));
    
    printf("popped %d from the stack\n",pop(sp));
    printf("popped %d from the stack\n",pop(sp));
    printf("popped %d from the stack\n",pop(sp));
    
    return 0;
}