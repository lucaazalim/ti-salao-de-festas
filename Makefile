CC = gcc
CFLAGS = -Wall -Wextra -std=c11

SRCDIR = src
OBJDIR = obj
BINDIR = bin

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
TARGET = $(BINDIR)/app

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning $(OBJS)..."
	@echo "Cleaning $(TARGET)..."
	rm -f $(OBJS) $(TARGET)
