#include <stdio.h>
#include <ctype.h>
#include <string.h>

char stack[100];
int top = -1;

void push(char c){ stack[++top] = c; }
char pop(){ return stack[top--]; }
int prec(char c){
    if(c=='+'||c=='-') return 1;
    if(c=='*'||c=='/') return 2;
    return 0;
}
void infixToPostfix(char* infix, char* postfix){
    int i=0,j=0; char c;
    while((c=infix[i++])!='\0'){
        if(isdigit(c)) postfix[j++]=c;
        else{
            postfix[j++]=' ';
            while(top!=-1 && prec(stack[top])>=prec(c))
                postfix[j++]=pop();
            push(c);
        }
    }
    while(top!=-1) postfix[j++]=pop();
    postfix[j]='\0';
}
int evaluatePostfix(char* postfix){
    int s[100],t=-1,i=0,val1,val2;
    char c;
    while((c=postfix[i++])!='\0'){
        if(isdigit(c)) s[++t]=c-'0';
        else if(c!=' '){
            val2=s[t--];
            val1=s[t--];
            if(c=='+') s[++t]=val1+val2;
            else if(c=='-') s[++t]=val1-val2;
            else if(c=='*') s[++t]=val1*val2;
            else if(c=='/') s[++t]=val1/val2;
        }
    }
    return s[t];
}
int main(){
    char infix[100],postfix[100];
    printf("Enter expression:");
    gets(infix);
    infixToPostfix(infix,postfix);
    printf("Result=%d\n",evaluatePostfix(postfix));
    return 0;
}
