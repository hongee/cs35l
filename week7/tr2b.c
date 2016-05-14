#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  if(argc < 3) {
    fprintf(stderr, "Incorrect number of inputs!\n");
    exit(1);
  }

  char* from = argv[1];
  char* to = argv[2];

  //input error checking
  if(strlen(from) != strlen(to)) {
    fprintf(stderr, "'From' and 'To' do not have the same length!\n");
    exit(1);
  }

  short marker[256];
  for (size_t i = 0; i < 256; i++) {
    marker[i] = 0;
  }
  for (size_t i = 0; from[i] != '\0'; i++) {
    if(marker[from[i]] != 0) {
      fprintf(stderr, "Input is ambigious!\n");
      exit(1);
    }
    marker[from[i]] = i + 1;
  }

  char c = getchar();

  while(c != EOF) {
    if(marker[c] != 0) {
      putchar(to[marker[c] - 1]);
    } else {
      putchar(c);
    }
    c = getchar();
  }
}
