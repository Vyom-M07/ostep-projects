#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
#define BIT_SHIFTER 8

int main(int argc, char* argv[]) {
  if (argc == 1) {
    printf("wzip: file1 [file2 ...]\n");
    exit(1);
  }

  // 1. read from a file
  // 2. grab each line of the file and use RLE zip algorithm to
  FILE* fp;
  //   size_t size;
  unsigned char buffer[5];
  // this will be for reading lines from the initial textfile
  char* line = NULL;
  size_t len = 0;
  ssize_t nread;
  for (int i = 0; i < argc - 1; i++) {
    fp = fopen(argv[i + 1], "r");
    if (!fp) {
      printf("wzip: cannot open file \n");
      exit(1);
    }
    while (((nread = getline(&line, &len, fp)) != -1)) {
      uint32_t repeats = 1;
      // this will grab the char, and before the position of the pointe updates
      // will keep the last repeated char

      //   printf("*line before if statement: %c\n", *line);
      while (*line == *(line + 1)) {
        repeats++;
        line++;
        // printf("*line after if statement: %c\n", *line);
      }
      // for loop here to fill the buffer
      for (int i = 0; i < 4; i++) {
        buffer[i] = (repeats & (0xFF << (i * BIT_SHIFTER)));
        // printf("buffer at index %d: %x\n", i, buffer[i]);
      }
      buffer[4] = *line;
      fwrite(buffer, sizeof(*buffer), ARRAY_SIZE(buffer), stdout);
      repeats = 1;
      line++;
    }
  }

  return 0;
}