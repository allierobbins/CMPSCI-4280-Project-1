#ifndef NODE_H
#define NODE_H 

#include <vector>
#include <string>
#include "token.h"

using namespace std;

/* Node definition */
struct Node {
	string name;
	struct Node *child1;
	struct Node *child2;
	struct Node *child3;
	struct Node *child4;
	vector<token*> TK;
	int level;
};

#endif
