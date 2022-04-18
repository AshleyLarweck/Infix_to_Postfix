#include "Stack.h"
#include <stdlib.h>
#include <stdio.h>

Stack newStack(int maximumStackSize)
{
        Element* array = (Element*)malloc(maximumStackSize * sizeof(Element));  
        StackImp* newStack = (StackImp*)malloc(2 * sizeof(int) + sizeof(array));
        newStack->maxSize = maximumStackSize;
        newStack->count = 0;
        newStack->stackElements = array;
        return newStack;

}

void push(Stack s, Element el)
{
        if(s->maxSize <= s->count)
        {
                s->maxSize *= 2;
                s->stackElements = realloc(s->stackElements, s->maxSize * sizeof(Element));
        }
        else
        {
          s->stackElements[s->count] = el;
          s->count++;
        }
}

Element pop(Stack s)
{
        int top = s->count-1;
        if(isEmpty(s) == 1)
        {

        }
        else
        {
                s->count--;
                return s->stackElements[top];
        }

}

int isEmpty(Stack s)
{
        if(s->count == 0)
        {
                return 1;
        }

        else
        {
                return 0;
        }
}

Element topElement(Stack s)
{

                return s->stackElements[s->count - 1];
        
}

void freeStack(Stack s)
{
        free(s->stackElements);
        free(s);
}