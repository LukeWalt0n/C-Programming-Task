#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    //Indexes the top of the stack - will increase by one each time a value is pushed
    //or decrease by 1 each time a value is popped
    int top_of_stack;   
    
    //Size of the stack.
    int size_of_stack;
    //An array of pointers to the information we're actually going to be storing.
    double* data;
    double num1;
    double num2;
    double number_to_push;
}Stack;


//Function that returns a pointer to the stack.
Stack* initialiseStack(int sizeOfStack){

    //Create the pointer:
    Stack* stack = malloc(sizeof(Stack));
    stack->size_of_stack = sizeOfStack; //Initialise the size of the stack.
    stack->top_of_stack = -1; //Set to -1 as no values have been added yet.
    stack->data = malloc(stack->size_of_stack * sizeof(double));   //Create the array, with the same size as the stack.

    return stack; //Return the pointer.
}

double pushToStack(Stack* stack, double num){
    
    //If we are at the last element in the array:
    stack->top_of_stack++;
    //Write the number to the array.
    stack->data[stack->top_of_stack] = num;
    return 1;
}

double popFromStack(Stack* stack){
    stack->top_of_stack--;
    
}

void setNumbersForCalculation(Stack* stack){
    stack->num1 = stack->data[stack->top_of_stack];
    popFromStack(stack);
    stack->num2 = stack->data[stack->top_of_stack];
    popFromStack(stack);
}

double subtract(Stack* stack){
    setNumbersForCalculation(stack);

    stack->number_to_push = stack->num1 - stack->num2;
    return pushToStack(stack, stack->number_to_push);
}

double add(Stack* stack){
    
    setNumbersForCalculation(stack);
    stack->number_to_push = stack->num1 + stack->num2;
    return pushToStack(stack, stack->number_to_push);
}


double multiply(Stack* stack){
    setNumbersForCalculation(stack);
    stack->number_to_push = stack->num1 * stack->num2;
    return pushToStack(stack, stack->number_to_push);
}

double divide(Stack* stack){
    //Cannot divide by 0!
    if(stack->data[stack->top_of_stack + 1] == 0){
        return 0;
    }
    else{
        setNumbersForCalculation(stack);
        stack->number_to_push = stack->num1 / stack->num2;
        pushToStack(stack, stack->number_to_push);
        return 1;
    }
    
}


void printStack(Stack* stack){
    for(int i =0; i < stack->size_of_stack; i++){
        if(i == stack->top_of_stack){
            printf("Top of stack: %.2f\n", stack->data[i], i);
        }
        else{
            printf("               %.2f\n", stack->data[i], i);
        }
        
    }
}


int determineInstruction(Stack* stack, char* operation){
    if(strcmp(operation, "add\n") == 0){
        //Call the add function.
        if(add(stack) == 1){
            printf("Added successfully\n");
            return 1;
        }
        else{
            printf("Error while adding");
            return 0;
        }
    }
    else if(strcmp(operation, "subtract\n") == 0){
        //Call the subtract function.
        if(subtract(stack) == 1){
            printf("subtracted successfully\n");
            return 1;

        }
        else{
            printf("Error when subtracting");
            return 0;
        }
    }
    else if(strcmp(operation, "multiply\n") == 0){
        //Call the multiply function
        if(multiply(stack) == 1){
            printf("Multiplied successfully\n");
            return 1;
        }
        else{
            printf("Error when multiplying\n");
            return 0;
        }
    }
    else if(strcmp(operation, "divide\n") == 0){
        //Call the divide function
        if(divide(stack) == 1){
            printf("Divided successfully\n");
            return 1;
        }
        else{
            printf("ERROR: DIVIDE BY ZERO\n");
            return 0;
            
        }
    }
    else if(strcmp(operation, "negate") == 0){
        //call the negate function
    }
    else if(strcmp(operation, "square") == 0){
        //call the square function.
    }
    else{
        printf("Error - operation not valid\n");
    }
}









int main(){
    //Create a 'stack' of size 10.
     Stack* stack = initialiseStack(2);
    
    

    //File handling:

    FILE *fileHandle;
    fileHandle = fopen("sum1.txt", "r");

    if(fileHandle == NULL){
        printf("Unable to access file!");
        return 1;
    }

    char buffer[200];
    char *result;
    double number;
    while(result = fgets(buffer, 200, fileHandle)){

            //Read each line and decide what to do.

            //See if we can read a number
            number = atof(result);
            if(number == 0 && result[0] != 0){
                //Not a number and therefore must be an instruction.
                printf("%s", result);
                if(determineInstruction(stack, result) == 1){
                        //Just continue.
                }
                else{
                    return 1;
                }
            }
            else{
                //Is a number so push to the stack.
                if(pushToStack(stack, number) == 1){
                    printf("Pushed %.2f to stack\n", number);
                    
                }
                else{
                    printf("Cannot push to stack - stack is full\n");
                }
            }
            printStack(stack);
    }
    printf("%.2f", stack->data[stack->top_of_stack]);

    
    
    
    
}
