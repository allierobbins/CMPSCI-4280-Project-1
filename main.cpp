#include "project4.h" 

/* Global Variable Declarations */
char *data = new char[1000];
int index = 0;
int lineNum = 1;

int main(int argc, char *argv[]) {

  printf("This is main.cpp. Beginning program.\n");

  /* If no arguments were passed to the program */
  if (argc == 1) {
    printf("MAIN ERROR : You must pass a file to the program.\nAborted.\n");
    exit(EXIT_FAILURE);

    /* If there is one argument passed to the program */
    } else if (argc == 2) {

        /* Assign input file name to variable */

          /*string fileName = argv[1];
          inFile.open(fileName + ".fs18");*/

        string inputFile(argv[1]);
        inputFile.append(".fs18");
        FILE *testOpen = fopen(inputFile.c_str(), "r");

        /* if file could not be opened */
        if (!testOpen) {
          printf("MAIN ERROR : File not found or could not be opened.\nAborted.\n");
				  exit(EXIT_FAILURE);
			    }

        /* Pass the file to a function to store all data in a character array */
        int size = fileToDataArray(inputFile.c_str(), data);

        /* for (int i = 0; i < 55; i++)
          cout << data[i]; */

        /* Declare the root node and call the parser */
        Node *root;
        root = parser();

        /* Parse Tree Generation */
        //testTree(root, 0);
        //printf("\nTree Generation Complete.\n\n");

        /* Call the Semantics function */
        codeGeneration(root, argv[1]);

    /* If too many arguments were passed to the program */
    } else if (argc > 2) {
        printf("MAIN ERROR : You've entered too many arguments. \nAborted.\n");
        exit(EXIT_FAILURE);
    }

   printf("Exiting main.cpp. Program completed.\n");
   return 0;

}/* End of main */

/* Function to transfer file data to a character array */
int fileToDataArray(string fileName, char *charArray) {

  /* Variable Declarations */
	int size = getFileSize(fileName);
	int num = 0;
	FILE *file = fopen(fileName.c_str(), "r");

	if(file) {

    /* Read from the input file and store values into array */
		char value;
		while(true) {

			value = fgetc(file);

      /* If reader reaches the end of a line, assign \n value */
			if (value == '\n') {
				charArray[num] = value;
				num++;
				continue;

      /* If reader reaches the end of the file, assign EOF value */
			} else if (value == EOF) {
				charArray[num] = '\0';
				break;

			} else if (value == '\t') {
				size--;
				continue;

      } else if (value == '\r') {
  				charArray[num] = '\n';
  				num++;
  				continue;

      /* If reader finds a comment, assign # value */
			} else if(value == '#') {
				charArray[num] = value;
				num++;

        /* Ignore the comment values until a WS is reached */
				do {
					value = fgetc(file);
					size--;
				} while(value != ' ');

				continue;

      /* If reader finds a "standard" element, save to array */
			} else {
				charArray[num] = value;
				num++;
			}
		}

  /* If the input file could not be opened, exit program */
	} else {
		printf("MAIN ERROR : Could not open file \n");
		exit(EXIT_FAILURE);
	}

  /* Close the input file */
	fclose(file);
	charArray = (char*)realloc(charArray, size);

  /* Return file size to MAIN */
	return size;
}

/* Function to get the size of the input file */
int getFileSize(string fileName) {

  /* Open the input file */
	ifstream file(fileName.c_str(), ios::in);

  /* Calculate the difference between start & finish */
	file.seekg(0, ios::end);
	int size = file.tellg();
	file.close();

  /* Return file size */
	return size;
}
