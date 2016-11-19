BINFOLDER := bin/
INCFOLDER := inc/
SRCFOLDER := src/
OBJFOLDER := obj/

CC := g++
CFLAGS := -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic
FLAGS := -lm -std=c++11 -pthread

SRCFILES := $(wildcard $(SRCFOLDER)*.cpp)

all: $(SRCFILES:$(SRCFOLDER)%.cpp=$(OBJFOLDER)%.o)
	$(CC) $(CFLAGS) $(OBJFOLDER)*.o -o $(BINFOLDER)main $(FLAGS)

$(OBJFOLDER)%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ -I./$(INCFOLDER) $(FLAGS)

run:
	$(BINFOLDER)main

.PHONY: clean
clean:
	rm -rf $(OBJFOLDER)*
	rm -rf $(BINFOLDER)*