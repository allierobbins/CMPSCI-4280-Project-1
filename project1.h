#ifndef PROJECT1_H
#define PROJECT1_H

#include <iostream>
#include <unistd.h>
#include <fstream>
#include "token.h"
#include "testScanner.h"

using namespace std;

/* for Emergency exit of program*/
static volatile sig_atomic_t EMERGSTOP = 0;
static void setEMERGSTOP(int signo) {
  EMERGSTOP = 1;
}
struct sigaction act;

/* Prototypes */
int fileToDataArray(string, char *);
int getFileSize(string);

/* Variable Declarations */
char *data = new char[500];

#endif
