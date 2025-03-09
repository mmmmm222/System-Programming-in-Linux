/***************************************************/
/***************************************************/
/******************  Stack Linked Based ************/
/******************  Autor : moHmd Ali  ************/
/******************  Version : 1.00     ************/
/***************************************************/
/***************************************************/

#ifndef LINKED_STACK_H_
#define LINKED_STACK_H_

typedef u8 StackEntry;

typedef struct stackNode
{
    StackEntry Entry;
    struct stackNode *Next;

} StackNode;

typedef struct
{
    StackNode *Top;
    u16 Size;
} Stack;

void Stack_voidInit(Stack *ps);
void Stack_voidPush(StackEntry Copy_Element, Stack *ps);
void Stack_voidPop(StackEntry *pe, Stack *ps);
u8 StackEmpty(Stack *ps);
u8 StackFull(Stack *ps);
void Stack_voidClear(Stack *ps);
void Stack_voidTraverse(Stack *ps, void (*pf)(StackEntry));
u16 Stack_u16Size(Stack *ps);

#endif