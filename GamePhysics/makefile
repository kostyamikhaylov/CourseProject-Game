TAG = game
DEP = my_game
DEP0 = Collide
DEP1 = Object
DEP2 = Movable
DEP3 = Rotatable
DEP4 = Shootable
DEP5 = Killable
DEP6 = Bullet
HDRS = Object.h Movable.h Rotatable.h Shootable.h Killable.h Bullet.h
DEPS = $(DEP).cpp $(DEP0).cpp $(DEP1).cpp $(DEP2).cpp $(DEP3).cpp $(DEP4).cpp $(DEP5).cpp $(DEP6).cpp
FLAGS = -Wall -g -Weffc++ -lsfml-graphics -lsfml-window -lsfml-system
CC = g++


$(TAG): $(DEPS)
	$(CC) $^ -o $@ $(FLAGS)

$(TAG): $(HDRS)

clean:
	rm -f $(TAG)
