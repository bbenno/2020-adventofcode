CC := gcc
CFLAGS = -O3 -Wall

OBJECTS = main.c
EXECUTABLE ?= main

.DEFAULT_GOAL := $(EXECUTABLE)

.PHONY: run
run: input $(EXECUTABLE)
	./$(EXECUTABLE) $<

.PHONY: clean
clean:
	rm -f $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)
