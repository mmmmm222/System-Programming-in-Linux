/***************************************************/
/***************************************************/
/******************  Stack Linked Based ************/
/******************  Autor : moHmd Ali  ************/
/******************  Version : 1.00     ************/
/***************************************************/
/***************************************************/

#ifndef LINKED_STACK_H_
#define LINKED_STACK_H_

typedef unsigned char u8;
typedef signed char s8;

typedef unsigned short int u16;
typedef signed short int s16;

typedef unsigned long int u32;
typedef signed long int s32;

typedef float f32;
typedef double f64;



typedef char* StackEntry;

typedef struct stackNode
{
    StackEntry Entry;
    struct stackNode *Next;

} StackNode;

typedef struct
{
    StackNode *Top;
    StackNode *Temp;
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
