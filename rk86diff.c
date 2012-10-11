#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "rk86fmt.h"
#include "i8080dis.h"

const char* const from_rk86[256] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  " ",  "!",  "\"",  "#",  "$",  "%",  "&",  "'",
  "(",  ")",  "*",  "+",  ",",  "-",  ".",  "/",
  "0",  "1",  "2",  "3",  "4",  "5",  "6",  "7",
  "8",  "9",  ":",  ";",  "<",  "=",  ">",  "?",
  "@",  "A",  "B",  "C",  "D",  "E",  "F",  "G",
  "H",  "I",  "J",  "K",  "L",  "M",  "N",  "O",
  "P",  "Q",  "R",  "S",  "T",  "U",  "V",  "W",
  "X",  "Y",  "Z",  "[",  "\\",  "]",  "^",  "_",
  "Ю",  "А",  "Б",  "Ц",  "Д",  "Е",  "Ф",  "Г",
  "Х",  "И",  "Й",  "К",  "Л",  "М",  "Н",  "О",
  "П",  "Я",  "Р",  "С",  "Т",  "У",  "Ж",  "В",
  "Ь",  "Ы",  "З",  "Ш",  "Э",  "Щ",  "Ч",  "~",
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

void instr(unsigned char const* const code, int ofs) {
  char cmd[1024];
  
  int i;
  printf(" | ");
  for (i = 0; i <= 2; ++i) {
    char const* const mark = ofs == -i ? "*" : "";
    printf("%s%02X%s", mark, code[ofs + i], mark);
  }

  i8080_disasm(code + ofs, cmd, sizeof(cmd) - 1);
  printf(" %-11s", cmd);
}

void cmp(const struct file_t* r1, const struct file_t* r2,
               int* from1, int sz1, int* from2, int sz2, char const* title,
               int disasm) {
  printf("> %s\n", title);

  int last_diff = -1;
  for (; sz1 > 0 && sz2 > 0; ++*from1, ++*from2, --sz1, --sz2) {
    int const v1 = r1->data[*from1];
    int const v2 = r2->data[*from2];
    char const c1 = (v1 >= 32 && v1 < 127) ? v1 : '.';
    char const c2 = (v2 >= 32 && v2 < 127) ? v2 : '.';
    char const* const rc1 = from_rk86[c1];
    char const* const rc2 = from_rk86[c2];

    if (v1 != v2) {
      if (last_diff != -1 && last_diff + 1 != *from1) printf("\n");
      printf("%04X/%04X: %02X %c %s != %02X %c %s",
             *from1, *from2, v1, c1, rc1, v2, c2, rc2);
      if (disasm) {
        instr(r1->data + *from1, - 2);
        instr(r1->data + *from1, - 1);
        instr(r1->data + *from1, 0);
      }
      printf("\n");
      last_diff = *from1;
    }
  }

  for (; sz1 > 0; ++*from1, --sz1) {
    int const v = r1->data[*from1];
    char const c = (v >= 32 && v <= 127) ? v : '.';
    char const* const rc = from_rk86[c];
    printf("%04X     : %02X %c %s\n", *from1, v, c, rc);
  }

  for (; sz2 > 0; ++*from2, --sz2) {
    int const v = r2->data[*from2];
    char const c = (v >= 32 && v <= 127) ? v : '.';
    char const* const rc = from_rk86[c];
    printf("----/%04X: -- - -    %02X %c %s\n", *from2, v, c, rc);
  }
}

int main(int argc, char* argv[]) {
  struct file_t r1, r2;  
  if (argc < 3) {
    fprintf(stderr, "RK86 diff  (C) 2012 by Alexander Demin\n");
    fprintf(stderr, "Usage: %s file1 file2\n", argv[0]);
    exit(1);
  }

  printf("File 1: %s\n", argv[1]);
  printf("File 2: %s\n", argv[2]);

  load_file(&r1, argv[1]);
  load_file(&r2, argv[2]);

  printf("======================================\n");
  printf("> Summary\n");
  print_caption();
  print_info(&r1);
  print_info(&r2);

  printf("======================================\n");

  int p1 = 0;
  int p2 = 0;

  cmp(&r1, &r2, &p1, r1.e6, &p2, r2.e6, "prolog", 0);
  cmp(&r1, &r2, &p1, 4, &p2, 4, "start/end address", 0);
  cmp(&r1, &r2, &p1, r1.sz, &p2, r2.sz, "text", 1);
  cmp(&r1, &r2, &p1, r1.gap, &p2, r2.gap, "trailing zeros", 0);
  cmp(&r1, &r2, &p1, r1.file_sz - p1, &p2, r2.file_sz - p2, "checksum", 0);
}
