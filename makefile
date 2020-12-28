CC     = gcc
CFLAGS = -g -Wall -std=c99
CCLINK = $(CC)
OBJS   = ransom.o
EXEC = prog.exe
RM = rm -rf *.o *.exe


$(EXEC): $(OBJS)
	$(CCLINK) $(OBJS) -o $(EXEC)

ransom.o: ransom.c
	$(CC) $(CFLAGS) -c ransom.c	

clean:
	$(RM)
