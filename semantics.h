#ifndef SEMANTICS_H
#define SEMANTICS_H

#include <iostream>
#include <unistd.h>
#include <fstream>
#include "node.h"
#include "token.h"
#include "stack.h"
#include "parser.h" 

/* Prototypes */
void codeGeneration(Node*, char*);
void semantics(Node*);
void check(token*);
int checkScope(stack);
int checkExists(stack);

#endif
