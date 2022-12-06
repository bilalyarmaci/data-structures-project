/* Data Structures Project - 12.2022 */
#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>

typedef struct stack{    // Stack structure (array implementation)
    char* dataArr;
    unsigned int count;
    unsigned int stackMax;
    int top;
}STACK;

// Creating a stack
STACK* createStack(int stackMax){
    STACK* stack;
    if((stack = malloc(sizeof(STACK)))){    // If allocating is successful
        stack->count=0;
        stack->stackMax = stackMax;
        if((stack->dataArr = (char*)calloc(stackMax,sizeof(char))))
            stack->top=-1;    // No data yet. 'stack->top' points to a meaningless index.
        else {    // If array allocation is not successful (presumably no memory available)
            printf("Stack array could not be initialized!\n"); 
            return NULL;
        }
        return stack;
    } else {    // If not successful (presumably no memory available)
        printf("Stack could not be initialized!\n");
        return NULL;
    }
}

// Adding data
bool push(STACK* stack, char dataIn){
    if(stack->top == stack->stackMax){    // When stack is full
        printf("Stack is full!\n");
        return false;
    }
    stack->top++;
    stack->dataArr[stack->top] = dataIn;
    stack->count++;
    return true;
}

// Popping data
char pop(STACK* stack){
    if(stack->count==0){    // If stack is empty
        printf("Stack is empty!\n");
        return 'a';    // A control character   
    }
    char popped = stack->dataArr[stack->top];
    stack->top--;
    stack->count--;
    return popped;
}

// Function to print the stack (not crucial)
void printStack(STACK* stack){
    int a = stack->count - 1;
    while(a>-1){    // Indexes start from 0, iterator should reach 0
        printf("%c ",stack->dataArr[a]);
        a--;
    }
    printf("\n");
}

// Checking function (KEY function)
bool balanced (const char p[], size_t n){
    STACK* tempStack = createStack(n);    // Temporary stack to hold possible complementing parentheses 
    char ch1;
    // 'i' is used for indexing. Indexes in C start from 0.
    for(int i = n-1; i >= 0; i--){    // (LIFO logic) iterating from top(back) to bottom(front)
        if((p[i]==41&&p[i-1]!=40)||(p[i]==125&&p[i-1]!=123))    // If p[i] and p[i-1] don't match then there could be a nested matching
            push(tempStack,p[i]);   // Holding for possible mathcing
        else if((p[i]==41&&p[i-1]==40)||(p[i]==125&&p[i-1]==123))   // If p[i] and p[i-1] match then iteration continues from p[i-2]
            i--;    // Manually decreasing iterator by 1 (one more time will be decreased by first condition with the next iteration)
        else {  // When nested mathcing
            if(tempStack->count!=0){    // If tempStack is not empty
                ch1 = pop(tempStack);   // LIFO logic   
                if((ch1==41&&p[i]!=40)||(ch1==125&&p[i]!=123)){    // If popped and p[i] don't match, then there is no balanced array of parentheses
                    free(tempStack);    // Free the allocated memory
                    return false;
                }
            } else {    // If tempStack is empty and 'i' is 0, then there is 1 unmatched bracket left in p[0]
                free(tempStack);
                return false;
            }
        }
    }
    if(n>1){    // If brackets are 2 or more then there is a possible balance in the array.
        free(tempStack);
        return true;
    } else{ // If brackets <= 1 there is no balance.
        free(tempStack);
        return false;
    }
     
}

int main(){
    unsigned int n;    // Number of entries
    char ch;
    printf("Number of entries: ");
    scanf("%d",&n);
    getchar();    // Catching the newline (ENTER) key from the stream
    STACK* myStack = createStack(n);
    while (n){    // Pushing allowed characters to myStack
        printf("Character: ");
        scanf("%c",&ch);
        getchar();
        if(ch==40||ch==41||ch==123||ch==125)    //ASCII codes for '( ) { }' respectively
            push(myStack,ch);
        n--;    // Iterator
    }
    puts(balanced(myStack->dataArr,myStack->count) ? "TRUE" : "FALSE");    // Answer
    return 0;
}