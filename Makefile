CC = cc
CFLAGS = -g -Werror -Wall -Wextra -Wformat=2 -Wbad-function-cast -Wcast-align -Wdeclaration-after-statement -Wdisabled-optimization -Wfloat-equal -Winline -Wmissing-declarations -Wmissing-prototypes -Wnested-externs -Wold-style-definition -Wpacked -Wpointer-arith -Wredundant-decls -Wstrict-prototypes -Wunreachable-code -Wwrite-strings
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
