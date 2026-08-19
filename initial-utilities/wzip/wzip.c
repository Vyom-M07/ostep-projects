#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
  if (argc == 1) {
    printf("wzip: file1 [file2 ...]\n");
    exit(1);
  }

  // 1. read from a file
  // 2. grab each line of the file and use RLE zip algorithm to
  //   size_t size;
  // this will be for reading lines from the initial textfile
  char* line = NULL;
  size_t len = 0;
  ssize_t nread;

  uint32_t repeats = 0;
  char current_char = -1;
  // printf("argc value: %d\n", argc);
  for (int i = i; i < argc; i++) {
    // printf("CL argument: %s\n", argv[i + 1]);
    FILE* fp = fopen(argv[i], "r");
    if (fp == NULL) {
      printf("wzip: cannot open file \n");
      exit(1);
    }
    while (((nread = getline(&line, &len, fp)) != -1)) {
      for (int j = 0; j < nread; j++) {
        if (current_char == -1) {
          // first character of the file
          current_char = line[j];
        } else if (current_char == line[j]) {
          // running sequence of repeat characters
          repeats++;
        } else {
          // enter else statement when change in letter detected

          // write the 'repeats' in binary
          fwrite(&repeats, sizeof(uint32_t), 1, stdout);
          // writes the letter we are repeating (e.g., 'a')
          fputc(current_char, stdout);

          current_char = line[j];
          repeats = 1;
        }
      }
    }
    fclose(fp);

    // final if-statement for last sequence of repeats
    // (since last seq will never detect a change in letter)
    if (current_char != -1) {
      fwrite(&repeats, sizeof(uint32_t), 1, stdout);
      fputc(current_char, stdout);
    }

    free(line);

    return 0;
  }