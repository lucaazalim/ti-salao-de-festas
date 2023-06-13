CC = gcc
CFLAGS = -Wall -Wextra -std=c11

SRCDIR = src
OBJDIR = obj
BINDIR = bin

TESTS_FILES = $(wildcard $(SRCDIR)/tests/*.c)

SRCS = $(wildcard $(SRCDIR)/**/*.c) $(wildcard $(SRCDIR)/*.c)
SRCS := $(filter-out $(TESTS_FILES), $(SRCS))
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
TARGET = $(BINDIR)/app

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)