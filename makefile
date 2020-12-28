CC     = gcc
CFLAGS = -g -Wall -std=c99
CCLINK = $(CC)
OBJS   = ransom.o
EXEC = prog.exe
RM = rm -rf *.o *.exe

$(EXEC): $(OBJ)
	$(CCLINK) $(OBJS) -o $(EXEC)

main.o: ransom.c
	$(CC) $(CFLAGS) -c ransom.c	

clean:
	$(RM)
