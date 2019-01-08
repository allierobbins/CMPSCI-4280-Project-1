#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>
#include "scanner.h"
#include "node.h"
 
extern std::ifstream inFile;

using namespace std;

/* Prototypes */
Node *parser();
Node *program();
Node *block();
Node *vars();
Node *mvars();
Node *expr();
Node *A();
Node *M();
Node *R();
Node *stats();
Node *mStat();
Node *stat();
Node *in();
Node *out();
Node *ifStatement();
Node *loop();
Node *assign();
Node *RO();
Node *createNode(string);

#endif
