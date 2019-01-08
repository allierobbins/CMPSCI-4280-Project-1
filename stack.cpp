#include "stack.h"

/* Global varialbes */
stack theStack[100];
deque<stack> theRealStack;
extern int loc;

/* Function to search the stack */
int searchRealStack(stack stk) {
	int size = theRealStack.size();
 
	if(!theRealStack.size()) {
		return -1;
	}

	for(int i = 0; i < theRealStack.size(); i++) {
		if((theRealStack[i].tokenWord == stk.tokenWord && theRealStack[i].scope == stk.scope)) {
			return theRealStack.at(i).lineNum;
		}
	}
	return -1;
}

/* Function to search the stact for an element */
int find(stack stk) {
	int size = theRealStack.size();
	stack temp;

	/* If the word is found in the stack - return its postition */
	for(int i = 0; i < size; i++) {
		if((theRealStack[i].tokenWord == stk.tokenWord) && (theRealStack[i].scope <= stk.scope)) {
			return i;
		}
	}

	/*If the element isn't on the stack → error */
	printf("'%s' hasn't been declared in this scope.\n", stk.tokenWord.c_str());
	exit(EXIT_FAILURE);
}

/* Function to search and puch to the stack */
void pushToRealStack(stack stk, FILE *file) {

	/* First check if the variable is new or used*/
	int result = searchRealStack(stk);

	/* If undeclared, push to stack. Else error */
	if(result == -1) {
		theRealStack.push_front(stk);
		fprintf(file, "PUSH %s\n", stk.tokenWord.c_str());
	} else {
		printf("'%s' was previously declared on line #%i\n", stk.tokenWord.c_str(), result);
		exit(EXIT_FAILURE);
	}
}

/* Function to search and pop from the stack */
void popFromRealStack(int scope, FILE *file, int &vars) {
	int size = theRealStack.size();
	size--;

	/* If the value is on the stack, pop it out */
	for(size; size >= 0; size--) {
		if(theRealStack[size].scope == scope) {
			fprintf(file, "POP %s\n", theRealStack[size].tokenWord.c_str());
			theRealStack.erase((theRealStack.begin() + size));
			vars--;
		}
	}
}

/* Function to search the stack for a value */
int searchStack(stack stk) {
	int pos = loc;
	for(pos; pos >= 0; pos--) {
		if((theStack[pos].tokenWord == stk.tokenWord) && (theStack[pos].scope == stk.scope)) {
			return theStack[pos].lineNum;
		}
	}
	return 0;
}

/* Function to search if a value is present on the stack */
int checkExists(stack stk) {
	int pos = loc;
	for(pos; pos >= 0; pos--) {
		if((theStack[pos].tokenWord == stk.tokenWord) && (theStack[pos].scope <= stk.scope)) {
			return pos;
		}
	}
	return -1;
}

/* Function to check if local/global variable */
int checkScope(stack stk) {
	int lo = checkExists(stk);
	if(lo >= 0) {
		if(theStack[lo].scope > stk.scope) {
			return 0;
		} else {
			return 1;
		}
	}
}

/* Function to push values to the stack */
void push(stack stk) {
	theStack[loc] = stk;
	loc++;
}

/* Function to pop values from the stack */
void pop(int scope, FILE *file, int &vars) {
	int pos = loc;
	stack temp;
	temp.tokenWord = "";
	temp.lineNum = -1;
	temp.scope = -1;

	if(scope > 0) {
		for(pos; pos >= 0; pos--) {
			if(theStack[pos].scope == scope) {
				theStack[pos] = temp;
				fprintf(file, "POP %s\n", temp.tokenWord.c_str());
				loc--;
				vars--;
			}
		}
		printf("\n");
	}
}

/* Overloaded function to pop values from the stack */
void pop(FILE *file, int &vars) {
	stack temp;
	temp.tokenWord = "";
	temp.lineNum = -1;
	temp.scope = -1;

	theStack[loc] = temp;
	fprintf(file, "POP %s\n", temp.tokenWord.c_str());
	loc--;
	vars--;
}
