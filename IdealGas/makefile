TAG = game
DEP = my_game
FLAGS = -Wall -g -Weffc++ -lsfml-graphics -lsfml-window -lsfml-system
CC = g++


$(TAG): $(DEP).cpp
	$(CC) $^ -o $@ $(FLAGS)

clean:
	rm -f $(TAG)
