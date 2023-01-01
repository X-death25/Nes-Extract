CC = cc
CFLAGS = -W -Wall -g
LDFLAGS =

SRC = main.c
OBJS = $(SRC:.c=.o)
AOUT = NesExtract

all : $(AOUT)

$(AOUT) : $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $>
%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<
clean :
	@rm -f *.o
cleaner : clean
	@rm -f $(AOUT)

.PHONY: all clean cleaner
