#ifndef SCANNER_H
#define SCANNER_H

#define FINAL 1000
#define ERROR -1

#include <iostream>
#include <unistd.h>
#include <fstream>
#include "token.h"
 
using namespace std;

/* Variable Declarations*/
extern char *data;
extern int index;
extern int lineNum;
extern string name;
extern token *TK;

/* Prototypes */
int checkIfKeyword(string);
int getNext(char);
string getKeyword(int);
token *scanner();
token *createNewToken(int, int, string);

#endif
