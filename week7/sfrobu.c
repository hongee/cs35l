#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int comps = 0;

int frobcmp(const void * pa, const void * pb) {
  const char * a = *(const char **) pa;
  const char * b = *(const char **) pb;
  comps++;
  int i;
  //printf("CMP:\n");
  //printf("%s\n", a);
  //printf("%s\n", b);
  for(i = 0; a[i] != ' ' && b[i] != ' '; i++) {
    int diff = (a[i] ^ 42) - (b[i] ^ 42);
    if(diff != 0)
      return diff;
  }

  //one ran out
  if(a[i] == b[i]) {
    return 0;
  } else if(a[i] == ' ') {
    //a ran out first
    //a less than b
    return -1;
  } else {
    //b ran out
    //a more than b
    return 1;
  }
}

int main() {
  char** wordList = NULL;
  char* regFile = NULL;
  int wordListLen = 0;
  int allocedMemSize = 0;
  int numChars = 0;

  struct stat fileStat;
  if(fstat(0, &fileStat) < 0) {
    //possibly not a regular file
    fprintf(stderr, "fstat failed on given input!\n");
    exit(1);
  } else {
    //fprintf(stderr, "File Size: %d bytes\n",fileStat.st_size);
    allocedMemSize = fileStat.st_size;
    regFile = (char*) malloc(allocedMemSize * sizeof(char) + 1);
    if(regFile == NULL) {
      fprintf(stderr, "Memory Allocation Failed!\n");
      exit(1);
    }
    read(0, regFile, allocedMemSize);
  }

  for (size_t i = 0; i < allocedMemSize; i++) {
    if(regFile[i] == ' ' || i == 0) {
      wordListLen++;
      //printf("%d\n", wordListLen);
      char ** temp = NULL;

      if(wordList) {
        temp = (char**) realloc(wordList, wordListLen * sizeof(char *));
      } else {
        temp = (char**) malloc(sizeof(char *));
      }

      if(temp == NULL) {
        fprintf(stderr, "Memory Allocation Failed!\n");
        exit(1);
      } else {
        wordList = temp;
        wordList[wordListLen - 1] = (i == 0 ? regFile : &regFile[i + 1]);
      }
    }
  }

  regFile[allocedMemSize] = ' ';

  //are there still stuff to be read?
  //revert to old strategy

  char c;
  int rval = read(0, &c, 1);

  while(rval != 0) {
    wordListLen++;
    //check if wordlist is null
    //if null - malloc sizeof(char*), else realloc len+1 * sizeof(char*)
    char ** temp = NULL;
    if(wordList) {
      temp = (char**) realloc(wordList, wordListLen * sizeof(char *));
    } else {
      temp = (char**) malloc(sizeof(char *));
    }

    if(temp == NULL) {
      fprintf(stderr, "Memory Allocation Failed!\n");
      exit(1);
    } else {
      wordList = temp;
    }

    //how many characters?

    char * strPtr = NULL;
    int strLen = 0;

    while(c != ' ' && rval != 0) {
      strLen++;
      char * temp = NULL;
      if(strPtr) {
        temp = (char *) realloc(strPtr, (strLen+1) * sizeof(char));
      } else {
        temp = (char *) malloc(2 * sizeof(char));
      }

      if(temp == NULL) {
        fprintf(stderr, "Memory Allocation Failed!\n");
        exit(1);
      } else {
        strPtr = temp;
      }

      strPtr[strLen - 1] = c;
      rval = read(0, &c, 1);
    }

    //write space char or break
    if(strPtr)
      strPtr[strLen] = ' ';
    else {
      wordListLen--;
      rval = read(0, &c, 1);
      continue;
    }

    wordList[wordListLen - 1] = strPtr;

    if(rval == 0)
      break;
    else
      rval = read(0, &c, 1);
  }


  char blankSpace = ' ';
  qsort(wordList, wordListLen, sizeof(char *), frobcmp);
  for(int i = 0; i < wordListLen; i++) {
    for(int j = 0; wordList[i][j] != ' '; j++) {
      write(1, &wordList[i][j], 1);
    }
    write(1, &blankSpace, 1);
  }
  fprintf(stderr, "Comparisons: %d\n", comps);
  exit(0);
}
