// name: Yulun Wang
// email: wang.yulun@northeastern.edu

// format of document is a bunch of data lines beginning with an integer (rank which we ignore)
// then a ',' followed by a double-quoted string (city name)
// then a ',' followed by a double-quoted string (population) - ignore commas and covert to int; or (X) - convert to 0
// then a lot of entries that are ignored


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

//struct bucket* hashTable = NULL;
int BUCKET_SIZE = 400;


// node struct
struct node {
    char key[MAXSTRING];
    int value;
    struct node* next;
};
// bucket struct
struct bucket{
    struct node* head;
    int count;
};
// create a new node
struct node* createNode(char *key, int value){
    struct node* newNode;
    newNode = (struct node*)malloc(sizeof(struct node));
    strcpy(newNode->key, key);
    //newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}
//  hash function with %
//int hashFunction1(int key){
//    return key % BUCKET_SIZE;
//}

// sum of character codes of city/state string
int sumCharacter(char *str){
    int sum = 0;
    for (int i=0; i<strlen(str);i++){
        sum = sum + str[i];
    }
    return sum;
}

// product of first 2 character codes in city/state string
int product(char *str){
    return (str[0] * str[1]);
}

// hash function alteration
int hashFunction(char *str, int hashFunctionNumber){
    int hashIndex;

    switch(hashFunctionNumber) {
      case 1:
	 hashIndex = strlen(str) % BUCKET_SIZE;
	 break;
      case 2:
	 hashIndex = sumCharacter(str) % BUCKET_SIZE;
         break;
      case 3:
	 hashIndex = product(str) % BUCKET_SIZE;
	 break;
      default:
	 printf("Invalid hash function\n");
	 break;
    }
    return hashIndex;
}

//  insert a new key
void add(char *str, int value, int hashFunctionNumber, struct bucket* hashTable){
    //int len = strlen(str);
    //int hashIndex = hashFunction1(len);
    int hashIndex = hashFunction(str,hashFunctionNumber);
    struct node* newNode = createNode(str, value);
    if (hashTable[hashIndex].count == 0){ // when node is empty
        hashTable[hashIndex].count = 1;
	hashTable[hashIndex].head = newNode;
    } else { // when node has a key
        newNode->next = hashTable[hashIndex].head;
	hashTable[hashIndex].head = newNode;
	hashTable[hashIndex].count++;
    }
}

// display the table
void display(struct bucket* hashTable){
    struct node* iterator;

    printf("\n==================\n");
    for (int i = 0; i<BUCKET_SIZE; i++){
        iterator = hashTable[i].head;
        printf("TABLE[%d]:\n", i);
        while (iterator != NULL)
        {
            printf("key/value: [%s] / [%d] \n", iterator->key, iterator->value);
            iterator = iterator->next;
        }
        printf("\n");
    }
    printf("\n================== \n");
}

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

  FILE* fp;
  fp = fopen("pop.csv","r");
  int i = 0;
  if (fp != NULL) {
    fgets(inputLine, MAXSTRING, fp); // prime the pump for the first line
    // ***** BEGIN FINTITE STATE MACHINE *****
    
    // STARTSTATE: digit -> S1
    // S1: digit -> S1; , -> S2
    // S2: " -> S3
    // S3: !" -> S3; " -> S4
    // S4: , -> S5
    // S5: " -> S6; ( -> ACCEPTSTATE
    // S6: digit -> S6; , -> S6; " -> ACCEPTSTATE; 
    // ACCEPTSTATE: done!
    // else go to ERRORSTATE
    //

    struct bucket* hashTable1;
    struct bucket* hashTable2;
    struct bucket* hashTable3;
    hashTable1 = (struct bucket *)malloc(BUCKET_SIZE * sizeof(struct bucket));
    hashTable2 = (struct bucket *)malloc(BUCKET_SIZE * sizeof(struct bucket));
    hashTable3 = (struct bucket *)malloc(BUCKET_SIZE * sizeof(struct bucket));


    while (feof(fp) == 0){
      nextChar = 0;
      state = STARTSTATE; 
      strcpy(temp,"");       // temp = ""

      if (nextChar >= strlen(inputLine)){
	// if no input string then go to ERRORSTATE
	state = ERRORSTATE;
      } 

      while ((state != ERRORSTATE) && (state != ACCEPTSTATE)) {
	switch (state) {
	  case STARTSTATE:
	    // look a digit to confirm a valid line
	    if (isDigit(inputLine[nextChar])) {
	      state = S1;
	      appendChar(temp, inputLine[nextChar]);
	    } else {
	      state = ERRORSTATE;
	    }  
	    break;


	  // ADD YOUR CODE HERE
	  case S1:
	    if (isDigit(inputLine[nextChar])) {
	      state = S1;
	      appendChar(temp, inputLine[nextChar]);
	    } else if (inputLine[nextChar] == ','){
	      state = S2;
	      //lineNum = strtol(temp, NULL, 10);
	      strcpy(temp, "");
	    } else {
	      state = ERRORSTATE;
	    }
	    break;

	  case S2:
	    if (inputLine[nextChar] == '\"'){
	      state = S3;
	    } else {
	      state = ERRORSTATE;
	    }
	    break;

	  case S3:
	    if (inputLine[nextChar] != '\"'){
	      state = S3;
	      appendChar(temp, inputLine[nextChar]);
	    } else if (inputLine[nextChar] == '\"'){
	      state = S4;
              strcpy(cityStr, temp);
	      strcpy(temp, "");
	    } else {
	      state = ERRORSTATE;
	    }
	    break;

	  case S4:
	    if (inputLine[nextChar] == ','){
	      state = S5;
	    } else {
	      state = ERRORSTATE;
	    }
	    break;

	  case S5:
	    if (inputLine[nextChar] == '"'){
	      state = S6;
	      popInt = 0;
	    } else if (inputLine[nextChar] == '('){
	      state = ACCEPTSTATE;
	      popInt = 0;
	    } else {
	      state = ERRORSTATE;
	    }
	    break;

	  case S6:
	    if (isDigit(inputLine[nextChar])){
	      state = S6;
	      int digit = inputLine[nextChar] - '0';
	      popInt = popInt *10 +digit;

	    } else if (inputLine[nextChar] == ','){
	      state = S6;
	    } else if (inputLine[nextChar] == '\"'){
	      state = ACCEPTSTATE;
	    } else {
	      state = ERRORSTATE;
	    }
	    break;

	  case ACCEPTSTATE:
	    // nothing to do - we are done!
	    break;
	    
	  default:
	    state = ERRORSTATE;
	    break;
	} // end switch

	// advance input
	nextChar++;
	
      }	// end while state machine loop

      // ***** END FINITE STATE MACHINE *****	  
      	

      // process the line - print out raw line and the parsed fields
      //printf("> %.60s\n", inputLine);
      //printf("[%.30s]: %d\n", cityStr, popInt); 
      //char* str_alloc = (char*)malloc(sizeof(cityStr));      
      
      add(cityStr, popInt, 1, hashTable1);
      add(cityStr, popInt, 2, hashTable2);
      add(cityStr, popInt, 3, hashTable3);

      // get next line
      fgets(inputLine, MAXSTRING, fp); 
    } // end while file input loop
    printf("\n***** HASH TABLE 1 *****\n");
    display(hashTable1);
    printf("\n***** HASH TABLE 2 *****\n");
    display(hashTable2);
    printf("\n***** HASH TABLE 3 *****\n");
    display(hashTable3);

    fclose(fp);
  
  } else {
    printf("File not found!\n");
  }
  
  return 0;
}
