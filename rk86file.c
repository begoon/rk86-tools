#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "rk86fmt.h"

int main(int argc, char* argv[]) {
  struct file_t r1;
  if (argc < 2) {
    fprintf(stderr, "RK86 file analyser  (C) 2012 by Alexander Demin\n");
    fprintf(stderr, "Usage: %s filename\n", argv[0]);
    exit(1);
  }

  printf("File: %s\n", argv[1]);
  load_file(&r1, argv[1]);
  printf("======================================\n");
  print_info(&r1);

  return 0;
}
