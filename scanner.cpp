#include "scanner.h"

/* scanner function that utilizes the FSA table to locate tokens (driver) */
token *scanner() {

	/* Variable Declarations */
	int current = FSATable[0][0];
	int lookAhead;
	int nextChar = getNext(data[index]);
	string word;
	token *TK; 

	/* While the scanner is running */
	while (current <= FINAL) {

		/* Find the current and look ahead values */
		nextChar = getNext(data[index]);
		lookAhead = FSATable[current][nextChar];

		if (lookAhead == ERROR) {
			printf("Scanner Error: scanner returned an error!\n");
			exit(EXIT_FAILURE);
		}

		/* If scanner returns a final state */
		if (lookAhead >= FINAL) {

			/* If value is an ID token */
			if (lookAhead == 1001) {

				/* Create and return the token */
				TK = createNewToken(lookAhead, lineNum, word);
				return TK;

			/* If value is a number token */
			} else if (lookAhead == 1002) {

				/* Create and return the token */
				TK = createNewToken(lookAhead, lineNum, word);
				return TK;

				/* If value is a special charater token */
			} else {

				/* If value is a WS, new line, or EOF, append the value */
				if(data[index] != ' ' && data[index] != '\n' && data[index] != '\0') {
						word.push_back(data[index]);
				}

				if(lookAhead == 1004 || lookAhead == 1006 || lookAhead == 1008 || lookAhead == 1009 || lookAhead >= 1010) {
					index++;
				}

				/* Create and return the token */
				TK = createNewToken(lookAhead, lineNum, word);
				return TK;
			}

			/* If the scanner returns a non-final state */
		} else {

			/* Move the placement marker to the lookAhead value */
			current = lookAhead;

			if(data[index] != '\n' && data[index] != ' ') {
				word.push_back(data[index]);
			}
		}

		/* If the next value is a new line - increment the line count */
		if(data[index] == '\n') {
			lineNum++;
		}

		/* Increment the index to read the next position */
		index++;
	}
}

/* Returns the ASCII value of the next character in the inputdata array */
int getNext(char ch) {
	if(isalpha(ch)) {
		return 1;
	} else if(isdigit(ch)) {
		return 2;
	} else if(ch == '\n') {
		return 24;
	} else if(ch == '\0') {
		return 25;
	} else {

		int num = ch;
		switch(num) {
			case 13:			/* Carriage Return */
				return 0;
			case 32:			/* WS */
				return 24;
			case 33:			/* ! */
				return 6;
			case 35:			/* # */
				return 23;
			case 37:			/* % */
				return 13;
			case 38:			/* & */
				return 12;
			case 40:			/* () */
				return 15;
			case 41:			/* ) */
				return 16;
			case 42:			/* * */
				return 10;
			case 43:			/* + */
				return 8;
			case 44:			/* , */
				return 17;
			case 45:			/* - */
				return 9;
			case 46:			/* . */
				return 14;
			case 47:			/* / */
				return 11;
			case 58:			/* : */
				return 7;
			case 59:			/* ; */
				return 20;
			case 60:			/* < */
				return 4;
			case 61:			/* = */
				return 3;
			case 62:			/* > */
				return 5;
			case 91:			/* [ */
				return 21;
			case 93:			/* ] */
				return 22;
			case 123:			/* { */
				return 18;
			case 125:			/* } */
				return 19;
			default:			/* If invalid char value - Scanner Error*/
				printf("Scanner Error : Invalid character: %c\nAborted.\n", (char)num);
				exit(EXIT_FAILURE);
		}
	}
}

/* Check if the passed string is a keyword defined by the language */
int checkIfKeyword(string word) {
	for(int i = 0; i < 12; i++) {
		if(!(word.compare(keywords[i]))) {
			return 1;
		}
	}
	return 0;
}

/* function to assign the string value of the token */
token *createNewToken(int ID, int line, string word) {

	/* Variable Declarations */
	token *tempTK = new token;

	tempTK->tokenID = ID;
	tempTK->line = line;

	/* Using the values indicated by the FSA Table - assign the proper token type */
	if(ID == 1100) {
		tempTK->tokenType = "EOF TK";
		tempTK->tokenWord = "EOF";
		return tempTK;
	} else if(ID == 1001) {
		tempTK->tokenType = "ID TK";
	} else if(ID == 1002) {
		tempTK->tokenType = "NUM TK";
	} else if(ID == 1003) {
		tempTK->tokenType = "= TK";
	} else if(ID == 1004) {
		tempTK->tokenType = "== TK";
	} else if(ID == 1005) {
		tempTK->tokenType = "< TK";
	} else if(ID == 1006) {
		tempTK->tokenType = "<< TK";
	} else if(ID == 1007) {
		tempTK->tokenType = "> TK";
	} else if(ID == 1008) {
		tempTK->tokenType = ">> TK";
	} else if(ID == 1009) {
		tempTK->tokenType = "=! TK";
	} else if(ID == 1010) {
		tempTK->tokenType = ": TK";
	} else if(ID == 1011) {
		tempTK->tokenType = "+ TK";
	} else if(ID == 1012) {
		tempTK->tokenType = "- TK";
	} else if(ID == 1013) {
		tempTK->tokenType = "* TK";
	} else if(ID == 1014) {
		tempTK->tokenType = "& TK";
	} else if(ID == 1015) {
		tempTK->tokenType = "% TK";
	} else if(ID == 1016) {
		tempTK->tokenType = ". TK";
	} else if(ID == 1017) {
		tempTK->tokenType = "( TK";
	} else if(ID == 1018) {
		tempTK->tokenType = ") TK";
	} else if(ID == 1019) {
		tempTK->tokenType = ", TK";
	} else if(ID == 1020) {
		tempTK->tokenType = "{ TK";
	} else if(ID == 1021) {
		tempTK->tokenType = "} TK";
	} else if(ID == 1022) {
		tempTK->tokenType = "; TK";
	} else if(ID == 1023) {
		tempTK->tokenType = "[ TK";
	} else if(ID == 1024) {
		tempTK->tokenType = "] TK";
	} else if(ID == 1025) {
		tempTK->tokenType = "[ TK";
	} else if(ID == 1026) {
		tempTK->tokenType = "/ TK";
	} else {
		printf("Scanner Error : Found token that does not exist: %i\n", ID);
		exit(EXIT_FAILURE);
	}

	if(checkIfKeyword(word)) {
		tempTK->keyword = 1;
	} else {
		tempTK->keyword = 0;
	}

	tempTK->tokenWord = string(word);

	printf("\t\tType: %s - ID: %d - Line %d - Word: %s \n", tempTK->tokenType.c_str(), tempTK->tokenID, tempTK->line, tempTK->tokenWord.c_str());
	return tempTK;
}
