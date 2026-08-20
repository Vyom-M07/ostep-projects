#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define ARRAY_SIZE(arr) sizeof(arr) / sizeof(arr[0])

void interactiveMode();  // function prototype to let 'main' know this exists
void batchMode(char* batchFile);

int main(int argc, char* argv[]) {
  // first determine whether we are interactive mode or batch mode
  if (argc == 1) {
    // interactive mode; invoked just ./wish
    interactiveMode();
  } else if (argc == 2) {
    // batch mode; invoked ./wish [batch file]
    batchMode(argv[1]);  // pass in the batch file
  } else {
    // error; wrong amount of arguments specified
    exit(1);
  }
}

void interactiveMode() {
  bool loop = true;
  while (loop) {
    // should keep looping until we get exit command
  }
}

void batchMode(char* batchFile) {
  FILE* fp = fopen(batchFile, "r");
  if (!fp) {
    exit(1);  // bad batch file (this is prob what the github meant by 'bad').
  }
  char* line = NULL;
  size_t len = 0;
  ssize_t nread;
  while ((nread = getLine(&line, &len, fp)) != -1) {
    char* linePtr = line;
    // while we have lines in the text file

    // let's first parse the line up
    char* input[] = strsep(*linePtr, " ");
    // now we loop and check each word
    // giant if-elseif-else chain I guess
    for (int i = 0; i < ARRAY_SIZE(input); i++) {
      if (strcmp(input[i], "exit")) {
        exit(0);
      }
    }
  }
}