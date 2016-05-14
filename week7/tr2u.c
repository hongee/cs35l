#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

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

  char c[1]; //one byte buffer
  int rval = read(0, c, 1);

  while(rval != 0) {
    if(marker[c[0]] != 0) {
      write(1, &to[marker[c[0]] - 1], 1);
    } else {
      write(1, c, 1);
    }
    rval = read(0, c, 1);
  }
}
