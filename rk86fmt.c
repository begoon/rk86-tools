#include "rk86fmt.h"

#include <string.h>
#include <assert.h>

static long file_size(FILE* f) {
  long sz;
  assert(fseek(f, 0L, SEEK_END) != -1);
  sz = ftell(f);
  assert(sz != -1);
  rewind(f);
  return sz;
}

void load_file(struct file_t* r, char const* const name) {
  printf("======================================\n");
  printf("Loading: [%s]\n", name);

  memset(r, 0, sizeof(*r));
  strcpy(r->name, name);

  FILE *f = fopen(r->name, "r+b");
  assert(f != NULL);

  r->file_sz = file_size(f);
  printf("File size: %d\n", r->file_sz);
  assert(r->file_sz > 5);

  int loaded_sz = 0;
  while (!feof(f)) {
    int read = fread(r->data + loaded_sz, 1, sizeof(r->data), f);
    assert(read > -1);
    if (read == 0) break;
    loaded_sz += read;
  }
  assert(loaded_sz == r->file_sz);
  fclose(f);

  int p = 0;
  if (r->data[p] == 0xe6) {
    r->e6 = 1;
    ++p;
    printf("Found leading E6\n");
  }

  r->start = (r->data[p] << 8) | r->data[p + 1];
  printf("Start: %04X\n", r->start);
  p += 2;

  r->end = (r->data[p] << 8) | r->data[p + 1];
  printf("End  : %04X\n", r->end);
  p += 2;

  r->sz = r->end - r->start + 1;
  printf("Size : %04X\n", r->sz);
  assert(r->sz > 0);

  assert(p + r->sz < r->file_sz);

  r->real_check_sum = 0;
  int i;
  for (i = 0; i < r->sz - 1; ++i, ++p) {
    assert(p < r->file_sz);
    int v = r->data[p] | (r->data[p] << 8);
    r->real_check_sum = (r->real_check_sum + v) & 0xffff;
  }
  r->real_check_sum = (r->real_check_sum + r->data[p]) & 0xffff;
  ++p;
  printf("Actual check sum: %04X\n", r->real_check_sum);

  while (r->data[p] == 0) {
    printf("00\n");
    assert(p < r->file_sz);
    ++r->gap;
    ++p;
  }
  printf("Found %d trailing zero(s)\n", r->gap);

  assert(p < r->file_sz);
  assert(r->data[p] == 0xe6);
  r->e6_2 = 1;
  ++p;

  assert(p + 2 <= r->file_sz);
  r->check_sum = (r->data[p] << 8) | r->data[p + 1];
  printf("Check sum: %04X\n", r->check_sum);
  if (r->real_check_sum != r->check_sum)
    printf("Check sums don't match!\n");
  p += 2;

  while (p < r->file_sz) {
    printf("%02X\n", r->data[p]);
    ++r->tail;
    ++p;
  }
}

void print_caption() {
  printf("E6 From To   Size 00..    E6 SUM  (real) Tail   Name\n");
  printf("-- ---- ---- ---- ------- -- ----------- ------ ----\n");
}

void print_info(const struct file_t* r) {
  printf("%s ", r->e6 ? "E6" : "--");
  printf("%04X %04X %04X ", r->start, r->end, r->sz);
  printf("zeros=%d ", r->gap);
  printf("%s ", r->e6_2 ? "E6" : "--");
  printf("%04X (%04X) ", r->check_sum, r->real_check_sum);
  printf("tail=%d ", r->tail);
  printf("%s ", r->name);
  printf("\n");
}
