#include <stdio.h>
#include <stdlib.h>
#define max 100
typedef int ElemType;
typedef int bool;
typedef struct stack{
    ElemType elem[max];
    int top;
}stack;
void makenull(stack *s){
    s->top=-1;
}
bool empty(stack s){
    if(s.top<0)
        return 1;
    else
        return 0;
}
ElemType top(stack s){
    if(empty(s))
        return 0;
    else
        return s.elem[s.top];
}
void pop(stack *s){
    if(empty(*s))
        printf("empty\n");
    else{
        printf("%d\n",s->elem[s->top]);
        s->top--;
    }
}
void push(ElemType x,stack *s){
    if(s->top==max-1)
        printf("stack is full\n");
    else{
        s->top++;
        s->elem[s->top]=x;
    }
}
void print(stack s){
    while(!empty(s)){
        pop(&s);
    }
}
stack a;
int main()
{
    makenull(&a);
    push(4,&a);
    push(5,&a);
    push(8,&a);
    printf("出栈\n");
    pop(&a);
    push(11,&a);
    push(15,&a);
    push(3,&a);
    printf("*********************\n");
    printf("出栈\n");
    pop(&a);
    push(2,&a);
    push(7,&a);
    //a=makenull();
    printf("*********************\n");
    printf("出栈\n");
    pop(&a);
    printf("*********************\n");
    printf("出栈\n");
    pop(&a);
    printf("*********************\n");
    printf("出栈\n");
    pop(&a);
    printf("*********************\n");
    printf("出栈\n");
    pop(&a);
    push(23,&a);
    printf("*********************\n");
    printf("输出全部\n");
    print(a);
    return 0;
}
