#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
  // argv[0] is ./wgrep
  // argv[1] is the word we are looking for
  // argv[2...] are all the files to look inside
  // printf("arg count: %d\n", argc);
  // printf("argv 0: %s\n", argv[0]);
  // printf("argv 1: %s", argv[1]);
  if (argc == 1) {
    // if someone types in just './wgrep'
    printf("wgrep: searchterm [file ...]\n");
    exit(1);
  }
  char* line = NULL;
  size_t len = 0;
  ssize_t nread;
  char* keyword = argv[1];
  if (isatty(0)) {
    for (int i = 1; i < argc - 1; i++) {
      FILE* fp = fopen(argv[i + 1], "r");
      if (fp == NULL) {
        printf("wgrep: cannot open file\n");
        exit(1);
      }
      while (((nread = getline(&line, &len, fp)) != -1)) {
        // printf("readline: %s\n", line);
        // line contains the line read from the
        // file now we have to find the keyword within this line (.contains()
        // type vibe)
        if (strstr(line, keyword) != NULL) {
          printf("%s", line);
        }
      }
    }
  } else {
    while ((nread = getline(&line, &len, stdin)) != -1) {
      if (strstr(line, keyword) != NULL) {
        printf("%s", line);
      }
    }
  }
  free(line);
  return 0;
}