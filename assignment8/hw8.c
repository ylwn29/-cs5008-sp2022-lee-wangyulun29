// name: Yulun Wang
// email: wang.yulun@northeastern.edu


// please start with a copy of your hw7.c, rename it to hw.8
// and then complete the assignment


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MAXSTRING 200

// finite state machine states
#define STARTSTATE 0
#define S1 1
#define S2 2
#define S3 3
#define S4 4
#define S5 5
#define S6 6
#define ACCEPTSTATE 10
#define ERRORSTATE 11

// check if a character c is a digit
bool isDigit(char c) {
  if ('0' <= c && c <= '9') {
    return true;
  } else {
    return false;
  }
}

// append character c to string s
void appendChar(char* s, char c) {
  char charToStr[2];           // convert char to string
    charToStr[0] = c;
    charToStr[1] = '\0';          // put NUL to terminate string of one character
    strcat(s, charToStr);
}



int main () {

  char inputLine[MAXSTRING];   // temporary string to hold input line
  char cityStr[MAXSTRING];     // city name
  int  lineNum;                // line number (city rank)
  int  popInt;                 // population
  int  state;                  // FSM state
  int  nextChar;               // index of next character in input string
  char temp[MAXSTRING];        // temp string to build up extracted strings from input characters
  
} 
