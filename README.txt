This is the README file for Allie Robbins' Program Translation Project 1.
I have chosen to do Option 3: FSA Table + Driver.

All files were written in C++.

List of files included in program:
  - scanner.cpp
  - scanner.h
  - testScanner.cpp
  - testScanner.h
  - main.cpp
  - token.h
  - makefile
  - README.txt

To execute the program:
    Run command "make" to build/compile the programs.
    Run command "./scanner "fileName" to run a program after it is built.

To clean the object files:
    Run command "make clean".

Purpose of program:
    The purpose of this program is to read from an input file and identify tokens.

Outline of Project 1 by file:
  main.cpp - reads in the command line arguments
           - opens the filename from argv[1]
           - reads from the file and stores values to an array
           - launches testScanner.cpp
  testScanner.cpp - initializes counter variables and launches scanner.cpp
  scanner.cpp - creates token instances w/ data gathered from array
              - prints token data to the screen
