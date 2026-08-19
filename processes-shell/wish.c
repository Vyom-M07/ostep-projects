#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void interactiveMode(); // function prototype to let 'main' know this exists
void batchMode(char* batchFile);

int main(int argc, char* argv[]) {
   // first determine whether we are interactive mode or batch mode
   if (argc == 1) {
      // interactive mode; invoked just ./wish
      interactiveMode();
   } else if (argc == 2) {
      // batch mode; invoked ./wish [batch file]
      batchMode(argv[1]); // pass in the batch file
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
   FILE *fp = fopen(batchFile, "r");
   if (!fp) {
      exit(1); // bad batch file (this is prob what the github meant by 'bad').
   }
}