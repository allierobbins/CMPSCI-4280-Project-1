#include "testTree.h"

void testTree(Node *node, int level) {

		if (level == 0)
			printf("\nEntered Tree Generator.\n\n");
 

  /* If the tree is empty, return */
	if(node == NULL) {
		return;
	}

  /* For the level of the tree, enter the correct # of indents */
	string line;
	token *TK;
	for(int i = 0; i < level; i++) {
		line.append("  ");
	}

  /* Create the line using the node values */
	line.append(node->name.c_str());
	line.append(" ");
	for(int i = 0; i < node->TK.size(); i++) {
		TK = node->TK[i];
		line.append(TK->tokenWord);
		line.append("  ");
	}

  /* Print the line value */
	printf("%s\n", line.c_str());
	//cout << node->child1 << "-" << node->child2 << "-" << node->child3 << "-" << node->child4 << endl;


  /* Call the children in order */
	testTree(node->child1, level + 1);
	testTree(node->child2, level + 1);
	testTree(node->child3, level + 1);
	testTree(node->child4, level + 1);
}
