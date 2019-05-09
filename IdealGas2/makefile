TAG = game
DEP1 = my_game
DEP2 = Object
HEAD = Object.h
DEPS = $(DEP1).cpp $(DEP2).cpp
FLAGS = -Wall -g -Weffc++ -lsfml-graphics -lsfml-window -lsfml-system
CC = g++


$(TAG): $(DEPS) $(HEAD)
	$(CC) $^ -o $@ $(FLAGS)


clean:
	rm -f $(TAG)
