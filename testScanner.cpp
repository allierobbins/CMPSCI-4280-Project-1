#include "testScanner.h"

/* testScanner function used to call scanner.cpp */
void testScanner(int size) {

  int index = 0;
  int counter = 0;
  int passed;
  int lineNum = 1;

  while (counter < size){

    /* Call to scanner */
    passed = scanner(index, lineNum);

    if (passed != -1) {
      index = passed;
      counter++;
    }
  }
}
