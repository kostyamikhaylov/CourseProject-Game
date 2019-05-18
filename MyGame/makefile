TAG = game
DEP1 = my_game
DEP2 = Menus
DEP3 = Collide
DEP4 = Object
DEP5 = Movable
DEP6 = Rotatable
DEP7 = Shootable
DEP8 = Killable
DEP9 = Bullet
HDRS = $(DEP2).h $(DEP4).h $(DEP5).h $(DEP6).h $(DEP7).h $(DEP8).h $(DEP9).h
DEPS = $(DEP1).o $(DEP2).o $(DEP3).o $(DEP4).o $(DEP5).o $(DEP6).o $(DEP7).o $(DEP8).o $(DEP9).o
FLAGS = -Wall -g -Weffc++ -lsfml-graphics -lsfml-window -lsfml-system
CC = g++


$(TAG): $(DEPS)
	$(CC) $^ -o $@ $(FLAGS)

%.o: %.cpp
	$(CC) -c $^ -o $@ $(FLAGS)

$(TAG): $(HDRS)

clean:
	rm -f $(DEPS) $(TAG)
