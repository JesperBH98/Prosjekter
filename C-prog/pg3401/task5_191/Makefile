INCLDIR = ./include
CC = gcc
CFLAGS = -O2
CFLAGS += -I$(INCLDIR)

OBJDIR = obj

SRC = task5_server.c
OBJ = $(OBJDIR)/task5_server.o
DEPS = $(INCLDIR)/ewpdef.h

$(OBJDIR)/%.o: %.c $(DEPS)
	@mkdir -p $(OBJDIR)
	$(CC) -c -o $@ $< $(CFLAGS)

server: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o server

