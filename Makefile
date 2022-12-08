CC=gcc
CFLAGS=-Wall
FILES=scanner.c botomtotop.c parser.c code_generator.c instruction_list.c str.c symbol_table.c symstack.c
EXECUTABLE=ifj_proj

all : $(EXECUTABLE)
$(EXECUTABLE) : $(FILES)
		$(CC) $(CFLAGS) $(FILES) -o $(EXECUTABLE)

clean :
	rm -f *.o $(EXECUTABLE)