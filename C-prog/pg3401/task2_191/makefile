INCLDIR = ./include
CC = gcc
CFLAGS = -O2 -include stdio.h
CFLAGS += -I$(INCLDIR)

OBJDIR  = obj

_DEPS = task2_count.h task2_hash.h task2_sum.h
DEPS = $(patsubst %,$(INCLDIR)/%,$(_DEPS))

_OBJS = main.o task2_count.o task2_hash.o task2_sum.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

vpath %.c $(SRCDIR)

$(OBJDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

exam_task2: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)/*~ exam_task2

