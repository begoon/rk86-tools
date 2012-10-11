#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "rk86fmt.h"
#include "i8080dis.h"  

int main(int argc, char* argv[]) {
  struct file_t r;
  if (argc < 2) {
    fprintf(stderr, "RK86 disassembler  (C) 2012 by Alexander Demin\n");
    fprintf(stderr, "Usage: %s filename [addr] [nb_instr]\n", argv[0]);
    fprintf(stderr, "Example: %s 3FE 25\n", argv[0]);
    exit(1);
  }

  printf("File: %s\n", argv[1]);
  load_file(&r, argv[1]);

  int addr = 0;
  if (argc > 2) sscanf(argv[2], "%x", &addr);
  
  int nb = 20;
  if (argc > 3) sscanf(argv[3], "%d", &nb);
  
  printf("Disassembling from %04X, %d instruction(s)\n", addr, nb);

  const int offset = r.e6 + 4;
  addr += offset;
  
  printf("Addr/File  Bytes  Instruction\n");
  printf("---- ----  ------ -----------\n");

  while (nb-- > 0) {
    char instr[1024];
    *instr = 0;
    int const sz = i8080_disasm(r.data + addr, instr, sizeof(instr) - 1);
    printf("%04X/%04X: ", addr - offset, addr);
    int i;
    for (i = 0; i < sz; ++i)
      printf("%02X", (unsigned char)r.data[addr + i]);
    for (i = 0; i < 3 - sz; ++i) printf("  ");
    printf(" %s\n", instr);
    addr += sz;
  }
  
  return 0;
}
