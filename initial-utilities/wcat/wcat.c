#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  if (argc < 2) {
    return 0;
  }
  for (int i = 0; i < argc - 1; i++) {
    FILE* fp = fopen(argv[i + 1], "r");
    if (fp == NULL) {
      printf("wcat: cannot open file\n");
      exit(1);
    }
    char bufferArray[100];
    while (fgets(bufferArray, sizeof(bufferArray), fp) != NULL) {
      printf("%s", bufferArray);
    }
    fclose(fp);
  }
  return 0;
}