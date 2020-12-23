
#include <stdlib.h>
#include <stdio.h>
#include "Stack.h"

// use -1 as top index to show stack is empty
StackObj *
newStack() { //creates new stack, allocates memory
    StackObj *S;

    S = (StackObj *) malloc ((size_t) sizeof(StackObj));
    S->top = -1;	//nothing in the stack
    return S;
}
void
printStack (StackObj *S) { //prints content of stack
    int i;

    printf("goign to print stack contents %d element \n", S->top +1);
    for (i=0; i<= S->top; i++) {
	printf("stack index %d = %p\n", i, S->items[i]);

    }
}
void
deleteStack(StackObj * S) { //deletes stack
   S->top = -1;		// being neurotic
   free(S);
}


// return the number of elements in the stack
int
stackSize( StackObj * S) { //returns stack size

    return (S->top + 1);

}

void
*pop(StackObj *S){ //extracts element from top of stack
    if (S->top < 0 ) {  // out of stack items
        //printf("returning nothing, stack empty\n");
        return NULL;
    }
    else {
        //printf("pop returning node");
	return (S->items[S->top--]);
    }
}
void
push(StackObj *S,  void *ref){ //adds new element to top of stack

    //printf("pushing token ");
    if (S->top <  MAX_STACK - 1) {  // out of stack items
	S->items[++(S->top)] = ref;
    }
    else {
	fprintf(stderr, "sorry out of stack space\n");
    }

}
