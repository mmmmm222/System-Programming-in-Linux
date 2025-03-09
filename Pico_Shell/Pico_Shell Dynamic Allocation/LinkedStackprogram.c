/******************  Stack Linked Based    ************/
/******************  Autor : mohamed ali   ************/
/******************  Version : 1.01        ************/
/*****************   Date :  Feb 12, 2024  ************/
/******************************************************/
/******************************************************/

//#include "STD_TYPES.h"
#include "LinkedStackinterface.h"
#include <stdlib.h>
/* pn => pointer to node */
/* ps => pointer to stack */
/* next => pointer to the next node */

void Stack_voidInit(Stack *ps)
{
    ps->Top = NULL;
    ps->Size = 0;
}

void Stack_voidPush(StackEntry Copy_Element, Stack *ps)
{
    /*allocate a new node & pointing to it*/
    StackNode *pn = (StackNode *)malloc(sizeof(StackNode));
    /* push the element in the node */
    pn->Entry = Copy_Element;
    
    if(ps->Size == 0)
    {
	pn->Next = NULL;
    	ps->Top  = pn;
	ps->Temp = pn;
    }
    else{
    	/* make the node pointer point to the node which the top is pointing */
    	pn->Next = NULL;
    	/* make the top point to the node which we created recently */
    	ps->Temp->Next = pn;
	ps->Temp = pn;
    }
    ps->Size++;
}

void Stack_voidPop(StackEntry *pe, Stack *ps)
{
    StackNode *pn;
    *pe = ps->Top->Entry;
    pn = ps->Top;
    ps->Top = pn->Next;
    free(pn);
    ps->Size--;
}

u8 StackFull(Stack *ps)
{
    return 0;
}

u8 StackEmpty(Stack *ps)
{
    // if the stack is empty then the top is pointing to null (0) so return is !0 is 1 that indicates the stack is empty
    return !(ps->Top);
}

void Stack_voidClear(Stack *ps)
{
    StackNode *pn = ps->Top;
    while (pn)
    {
        pn = pn->Next;
        free(ps->Top);
        ps->Top = pn;
    }
    ps->Size = 0;
}

void Stack_voidTraverse(Stack *ps, void (*pf)(StackEntry))
{
    StackNode *pn = ps->Top;
    while (pn)
    {
        (*pf)(pn->Entry);
        pn = pn->Next;
    }
}

u16 Stack_u16Size(Stack *ps)
{
    return ps->Size;
}

