#ifndef RK86FMT_H
#define RK86FMT_H

#include <stdio.h>

struct file_t {
  char name[1024];
  int e6;
  int start;
  int end;
  int sz;
  int file_sz;
  unsigned char data[0x10000];
  int gap;
  int e6_2;
  int check_sum;
  int real_check_sum;
  int tail;
};

void load_file(struct file_t* r, char const* const name);
void print_info(const struct file_t* r);
void print_caption();

#endif
