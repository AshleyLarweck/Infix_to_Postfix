#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Stack.h"

#define MAX_LINE_LENGTH 50

int convertToPostfix(char *infixString, char *postfixString);
int evaluatePostfix(char *postfixString);

int main()
{
	FILE *inputFile;
	inputFile = fopen("p1Input.txt", "r");
	if(inputFile == NULL){

		perror("Error opening file");
		return -1;
	}

	//This string will hold the infix equations that are read from inputFile, one at a time.
	char infixString[MAX_LINE_LENGTH];


	//Use fgets to read the next line from the inputFile.
	//Store the line into infixString.
	//The while loop repeats until there are no more lines in the file.
	while(fgets(infixString, MAX_LINE_LENGTH, inputFile)!=NULL){

		//If the line is blank, skip it.
		if(infixString[0] == '\n')
			continue;

		printf("Current infix string: %s",infixString);

		//postfixString is a string to store the equation from szInfixString converted into postfix.
		char postfixString[MAX_LINE_LENGTH];

		//Call the convertToPostfix function (that you are to implement below main).
		int returnMessage = convertToPostfix(infixString,postfixString);


		//convertToPostfix should return an integer letting us know if the infix string was in a valid format.
		//If the format is valid (we returned 0), then we call the evalutaePostfix function (that you are to implement below), and print the result of the evalution.
		//If the format is not valid (we returned something other than 0), then we print the corresponding error message.
		switch(returnMessage)
		{

			case 0: //0 means the infix string had no errors.  Go ahead and evaluate the postfix string.
				printf("Postfix string: %s\n",postfixString);
				int result = evaluatePostfix(postfixString);
				printf("It evaluates to %d.\n",result);
				break;
			case 1:  //1 means the infix string is missing a left parenthesis.
				printf("WARNING: Missing left parenthesis.\n");
				break;
			case 2: //2 means the infix string is missing a right parenthesis.
				printf("WARNING: Missing right parenthesis.\n");
				break;
			case 3: // 3 means missing operator.
				printf("WARNING: Missing operator.\n");
				break;
			case 4: //4 means missing operand.
				printf("WARNING: Missing operand.\n");
				break;
			default:
				printf("WARNING: %d.\n", returnMessage);


		}


		printf("\n\n");
	}

	fclose(inputFile);

	return 0;
}


/*******
int convertToPostfix(char *infixString, char *postfixString)

Input: 
infixString is a character array of length <= MAX_LINE_LENGTH that contains an equation in infix format.
postfixString is a currently empty character array of length <= MAX_LINE_LENGTH that we should fill with a postfix representation of infixString.

Output:
We return an integer based on any errors found in infixString.
If there are no errors, return 0.
If there is a missing (, return 1.
If there is a missing ), return 2.
If there is a missing operator, return 3 (for extra credit).
If there is a missing operand, return 4 (for extra credit).
*********/
int convertToPostfix(char *infixString, char *postfixString)
{       
        int i = 0;
        int j = 0;
        char in;
        Stack s = newStack(MAX_LINE_LENGTH);

        in = infixString[i];    

        while(in != '\0')
        {

                if(in == '+' || in == '-' || in == '*' || in == '/')
                {
                        if(isEmpty(s) == 1)
                        {
                                Element n;
                                n.operation = in;
                                push(s, n);
                        }
           
                        else
                        {

                                if(in == '*' || in == '/')
                                {
  
                                        Element n;
                                        while(isEmpty == 0)
                                        {
                                                n = topElement(s);

                                                if(n.operation == '*' || n.operation == '/')
                                                {
                                                        n = pop(s);
                                                        
                                                        postfixString[j] = n.operation;
                                                        j++;
                                                }


                                        }

                                        Element w;
                                        w.operation = in;
                                        push(s, w);
                                }

                                if(in == '+' || in == '-')
                                {
                                        
                                        Element n;
                                        while(isEmpty(s) == 0)
                                        {
                                                n = topElement(s);
                                              
                                                if(n.operation != '(')
                                                {
                                                        n = pop(s);

                                                        postfixString[j] = n.operation;
                                                        j++;
                                                }
                                                else
                                                {
                                                        break;
                                                }
                                        }                       

                                        Element w;
                                        w.operation = in;
                                        
                                        push(s, w);
                                }
                        }
                }
                
                else if(in == '(')
                {
                        Element n;
                        n.operation = in;
                        push(s, n);
                }

                else if(in == ')')
                {
                        Element n;
                        n = topElement(s);

                        while(n.operation != '(')
                        {
                                n = pop(s);
                                                
                                if(isEmpty(s) == 1)
                                {
                                        
                                        freeStack(s);

                                        return 1;
                                }
                                postfixString[j] = n.operation;
                                j++;
                                n = topElement(s);
                        }

                        n = pop(s);

                        if(n.operation != '(')
                        {
                                freeStack(s);
                                
                                return 1;
                        }
                                                
                }

                else
                {
                        if(in == '\n')
                        {
                                break;
                        }
                        else
                        {
                                postfixString[j] = in;
                                j++;
                        }

                }

                i++;    
                in = infixString[i];

        }

        if(isEmpty(s) == 0)
        {
                Element n;
                
                while(isEmpty(s) != 1)
                {
                        n = topElement(s);
                        
                        if(n.operation == '(')
                        {
                                freeStack(s);

                                return 2;
                        }

                        else if(n.operation == '+' || n.operation == '-' || n.operation == '*' || n.operation == '/')
                        {
                                n = pop(s);

                                postfixString[j] = n.operation;
                                j++;
                        }


                }
        }

        postfixString[j] = '\0';

        freeStack(s);   

        return 0;
}


/************
evaluatePostfix(char *postfixString)

Input:
postfixString is a string of length <= MAX_LINE_LENGTH that contains an equation in postfix representation.
If your convertToPostfix() function is correct, this string should be in a valid postfix format.

Output:
Return an integer representing what the postfix equation evaluated to.
************/

int evaluatePostfix(char *postfixString)
{

        Stack s = newStack(MAX_LINE_LENGTH);
        int i = 0;
        Element w;
        Element x;
        int total;

        char in;
        in = postfixString[i];

        while(in != '\0')
        {

                if(isdigit(in))
                {

                        Element n;
                        n.operand = in - '0';
                        push(s, n);
                }

                else if(in == '+' || in == '-' || in == '*' || in == '/')
                {

                        w = pop(s);
                        x = pop(s);

                        switch(in)
                        {
                                case '+':
                                        total = w.operand + x.operand;
                                        break;
                                case '-':
                                        total = x.operand - w.operand;
                                        break;
                                case '*':
                                        total = w.operand * x.operand;
                                        break;
                                case '/':
                                        total = x.operand / w.operand;
                                        break;
                        }

                        Element a;
                        a.operand = total;
                        push(s, a);
                }

                i++;
                in = postfixString[i];
        }

        freeStack(s);
  
        return total;

}
