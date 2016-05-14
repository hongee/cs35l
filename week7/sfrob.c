#include <stdio.h>
#include <stdlib.h>

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
  int wordListLen = 0;

  char c = getchar();

  while(c != EOF) {
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

    char * strPtr = NULL;
    int strLen = 0;

    while(c != ' ' && c != EOF) {
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
      c = getchar();
    }

    //write space char
    if(strPtr)
      strPtr[strLen] = ' ';
    else {
      wordListLen--;
      c = getchar();
      continue;
    }

    wordList[wordListLen - 1] = strPtr;

    if(c == EOF)
      break;
    else
      c = getchar();
  }

  qsort(wordList, wordListLen, sizeof(char *), frobcmp);
  for(int i = 0; i < wordListLen; i++) {
    for(int j = 0; wordList[i][j] != ' '; j++) {
      putchar(wordList[i][j]);
    }
    putchar(' ');
  }
  fprintf(stderr, "Comparisons: %d\n", comps);
  exit(0);
}
