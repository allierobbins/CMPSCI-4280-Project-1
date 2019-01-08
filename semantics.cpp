#include "semantics.h"

static int scope = 0;
int loc = 0;
int loopCount = 0;
int variablesOnStack = 0;
int place = 0;
const char* variableTracker[50];
int varNum = 0;
  
FILE *file;

token *temp;

void codeGeneration(Node *root, char *name) {

  printf("\nEntered Code Generation.\nSemantics Position\tStack Information\n\n");

  /* Create the .asm output file w/ the input filename */
	string tempFile(name);
	string fileName = tempFile.substr(0, tempFile.find("."));
	fileName.append(".asm");

	file = fopen(fileName.c_str(), "w");

  /* If unable to open the output file = Error */
	if(file == NULL) {
		printf("SEMANTICS ERROR : Could not write output file.\n Aborted.\n");
		exit(EXIT_FAILURE);
	}

  /* Begin code generation w/ the root node */
	semantics(root);

  /* At the end of code generation, add final statements to output file */
	popFromRealStack(scope, file, variablesOnStack);
  fprintf(file, "STOP\n\n");

  /* Print the variable declaractions */
  for (int i = 0; i <= varNum; i++)
    fprintf(file, "%s\n", variableTracker[i]);

	while(place > 0) {
		fprintf(file, "%i 0\n", place - 1);
		place--;
	}

  printf("\nCode Generation completed - please see output file '%s'.\n\n", fileName.c_str());

}

/* Recurside semantics() - calls itself and reacts based on the node*/
void semantics(Node *root) {

  printf("%s\n", root->name.c_str());
  /* If the node is empty, explicit return */
	if(root == NULL) {
		return;
	}

	/* <program> → void <vars> <block> */
	if(root->name == "<program>") {
  		semantics(root->child1);
  		semantics(root->child2);
	}

	/* <block> → begin <vars> <stats> end */
	if(root->name == "<block>") {
		scope++;
		semantics(root->child1);
		semantics(root->child2);
		popFromRealStack(scope, file, variablesOnStack);
		scope--;
		return;
	}

	/* <vars> → empty | let Identifier = integer <vars> */
	if(root->name == "<vars>") {

		if(!root->TK.empty()) {
			temp = root->TK.front();
			root->TK.erase(root->TK.begin());

			stack test;
			test.tokenWord = temp->tokenWord;
			test.scope = scope;
			test.lineNum = temp->line;

      printf("\t\t\tTOKEN: %s\tLINE: %i\tSCOPE: %i\n", test.tokenWord.c_str(), test.lineNum, test.scope);
      variableTracker[varNum] = temp->tokenWord.c_str();
      varNum++;

			if(temp->tokenID == 1001) {
        check(temp);
				pushToRealStack(test, file);
        fprintf(file, "LOAD %s\n", temp->tokenWord.c_str());
				semantics(root->child1);
				variablesOnStack++;
			}
		} else {
			return;
		}
	}

	/* <expr> → <A> / <expr> | <A> * <expr> | <A> */
	if(root->name == "<expr>") {

		if(root->child2 != NULL) {
			int local = place;
			place++;

			/* <A> / <expr> */
			if(temp->tokenID == 1126) {
				semantics(root->child1);
        fprintf(file, "STORE %i\n", local);
				semantics(root->child2);
        fprintf(file, "DIVI %i\n", local);
				return;

				/* <A> * <expr> */
			} else if(temp->tokenID == 1013) {
				semantics(root->child2);
				fprintf(file, "STORE %i\n", local);
				semantics(root->child1);
				fprintf(file, "MULTI %i\n", local);
				return;
			}

		} else {
      semantics(root->child1);
      semantics(root->child2);
      return;
	}

	/* <A> → <M> + <A> | <M> - <A> | <M> */
	if(root->name == "<A>") {

		if(!root->TK.empty()) {
			int local = place;
			place++;

			temp = root->TK.front();
			root->TK.erase(root->TK.begin());

			/* <M> + <A> */
			if(temp->tokenID == 1011) {
				semantics(root->child1);
        fprintf(file, "STORE %i\n", local);
				semantics(root->child2);
        fprintf(file, "ADD %i\n", local);
				return;

				/* <M> - <A> */
			} else if(temp->tokenID == 1012) {
				semantics(root->child2);
				fprintf(file, "STORE %i\n", local);
				semantics(root->child1);
				fprintf(file, "SUB %i\n", local);
				return;
			}
		} else {
      semantics(root->child1);
      semantics(root->child2);
			return;
		}
	}

	/* <M> → - <M> | <R> */
	if(root->name == "<M>") {

		if(root->child1 == NULL) {
			semantics(root->child2);
			return;
		} else {
			semantics(root->child1);
			fprintf(file, "MULT -1\n");
			return;
		}
	}

	/* <R> → ( <expr> ) | Identifier | Number */
	if(root->name == "<R>") {

		if(!root->TK.empty()) {
			temp = root->TK.front();
			root->TK.erase(root->TK.begin());
			stack stk;

			stk.tokenWord = temp->tokenWord;
			stk.lineNum = temp->line;
			stk.scope = scope;

			if(temp->tokenID == 1001) {
				fprintf(file, "STACKR %i\n", find(stk));
				return;
			} else if(temp->tokenID == 1002) {
				fprintf(file, "LOAD %s\n", stk.tokenWord.c_str());
				return;
			}
		} else {
      semantics(root->child1);
			return;
		}
	}

	/* <stats> → <stat> <mStat> */
	if(root->name == "<stats>") {

    /* Call the child node(s) */
    semantics(root->child1);
    semantics(root->child2);

		return;
	}

	/* <mStat> → empty | <stat> <mStat> */
	if(root->name == "<mStat>") {

    /* Call the child node(s) if not empty */
		if(root->child1 != NULL) {
      semantics(root->child1);
      semantics(root->child2);

			return;
		}
	}

	/* <stat> → <in> | <out> | <block> | <if> | <loop> | <assign> */
	if(root->name == "<stat>") {

    /* Call the child node(s) */
    semantics(root->child1);
		return;
	}

	/* <in> → read ( Identifier ) : */
	if(root->name == "<in>") {

		if(!root->TK.empty()) {
			temp = root->TK.front();
			root->TK.erase(root->TK.begin());
			stack stk;

			stk.tokenWord = temp->tokenWord;
			stk.lineNum = temp->line;
			stk.scope = scope;

			int local = place;
			place++;

			fprintf(file, "READ %i\n", local);
			fprintf(file, "LOAD %i\n", local);
			fprintf(file, "STACKW %i\n", find(stk));
			return;
		}

		return;
	}

	/* <out> → print ( <expr> ) : */
	if(root->name == "<out>") {

		int local = place;
		place++;

    /* Call the child node(s) */
		semantics(root->child1);
		fprintf(file, "STORE %i\n", local);
		fprintf(file, "WRITE %i\n", local);
		return;
	}

	// <if> → cond ( <expr> <RO> <expr> ) <block>
	if(root->name == "<if>") {

		int thisLoop = ++loopCount;
		int local = place;
		place++;

    /* Call the child node(s) */
		fprintf(file, "\nloop%i: ", loopCount);
		/* Child 1 is <expr> */
		semantics(root->child1);
		fprintf(file, "STORE %d\n", local);
		/* Child 2 is <RO> */
		semantics(root->child3);
  	fprintf(file, "SUB %d\n", local);
		/* Child 3 is <expr> */
		semantics(root->child2);
		/* Child 4 is <block> */
		semantics(root->child4);
		fprintf(file, "end%d: NOOP\n\n", thisLoop);

		return;
	}

	/* <loop> → iter ( <expr> <RO> <expr> ) <stat> */
	if(root->name == "<loop>") {

		int thisLoop = ++loopCount;
		int local = place;
		place++;

    /* Call the child node(s) */
		fprintf(file, "\nloop%i: ", loopCount);
		/* Child 1 is <expr> */
		semantics(root->child1);
		fprintf(file, "STORE %d\n", local);
		/* Child 2 is <RO> */
		semantics(root->child3);
    fprintf(file, "SUB %d\n", local);
		/* Child 3 is <expr> */
		semantics(root->child2);
		/* Child 4 is <block> */
		semantics(root->child4);
		fprintf(file, "BR loop%d\n", thisLoop);

		fprintf(file, "end%d: NOOP\n\n", thisLoop);

		return;
	}

	/* <assign> → Identifier = <expr> : */
	if(root->name == "<assign>") {

    semantics(root->child1);

		if(!root->TK.empty()) {
			temp = root->TK.front();
			root->TK.erase(root->TK.begin());

			stack stk;
			stk.tokenWord = temp->tokenWord;
			stk.lineNum = temp->line;
			stk.scope = scope;

			fprintf(file, "STACKW %i\n\n", find(stk));
			return;

		}
	}

	/* <RO> → < | < = | > | > = | = = | = */
	if(root->name == "<RO>") {

		if(!root->TK.empty()) {
			temp = root->TK.front();
			root->TK.erase(root->TK.begin());

			if(temp->tokenWord == "<") {
				if(!root->TK.empty()) {
					token *temp2 = root->TK.front();
					root->TK.erase(root->TK.begin());

					if(temp2->tokenWord == "=") {
						fprintf(file, "BRNEG end%d\n", loopCount);
						return;
					}
				}

				fprintf(file, "BRZNEG end%d\n", loopCount);
				return;
			}

			if(temp->tokenWord == ">") {
				if(!root->TK.empty()) {
					token *temp2 = root->TK.front();
					root->TK.erase(root->TK.begin());

					if(temp2->tokenWord == "=") {
						fprintf(file, "BRPOS end%d\n", loopCount);
						return;
					}
				}

				fprintf(file, "BRZPOS end%d\n", loopCount);
				return;
			}

			if(temp->tokenWord == "=") {
				fprintf(file, "BRPOS end%d\n", loopCount);
				fprintf(file, "BRNEG end%d\n", loopCount);
				return;
			}
		}
	}
}
}

/* Function to check if a variable was already decalred */
void check(token *TK) {
	stack stk;
	stk.tokenWord = TK->tokenWord;
	stk.lineNum = TK->line;
	stk.scope = scope;

	int result = searchStack(stk);

  /* If variable was already declared - error. Else add it to the stack */
	if(result > 0) {
		cout << "Variable " << stk.tokenWord << " has been previously declared on line " << result << "\n";
		exit(EXIT_FAILURE);
	} else {
		push(stk);
	}
}
