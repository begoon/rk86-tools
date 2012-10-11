all: build
	
ifeq ($(OS),Windows_NT)
  CC = c:/tcc/tcc
  EXE = .exe
else
  CC = cc
endif

DIFF = rk86diff
FILE = rk86file
DISASM = rk86dis

build:
	$(CC) -o $(DIFF)$(EXE) rk86diff.c rk86fmt.c i8080dis.c
	$(CC) -o $(FILE)$(EXE) rk86file.c rk86fmt.c i8080dis.c
	$(CC) -o $(DISASM)$(EXE) rk86dis.c rk86fmt.c i8080dis.c

clean:
	-rm $(DIFF)$(EXE) $(FILE)$(EXE) $(DISASM)$(EXE)

