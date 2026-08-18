#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr[0])))

int main(int argc, char* argv[]) {
  if (argc == 1) {
    printf("wunzip: file1 [file2 ...]\n");
    exit(1);
  }
  FILE* fp;
  size_t ret;
  unsigned char buffer[5];
  for (int i = 0; i < argc - 1; i++) {
    fp = fopen(argv[i + 1], "rb");
    if (!fp) {
      printf("wunzip: cannot open file \n");
      exit(1);
    }
    while ((ret = fread(buffer, sizeof(*buffer), ARRAY_SIZE(buffer), fp)) ==
           ARRAY_SIZE(buffer)) {
      uint32_t repeats = 0;
      // we use 4 here because we are taking in 4 byte chunks
      for (int j = 0; j < 4; j++) {
        // printf("buffer at %d: %x\n", i, buffer[i]);
        repeats = repeats | ((buffer[j]) << (8 * j));
      }
      // printf("buffer at 4: %x\n", buffer[4]);
      // printf("repeats variable: %d\n", repeats);
      for (int j = 0; j < repeats; j++) {
        printf("%c", buffer[4]);
      }
    }
  }

  return 0;
}
