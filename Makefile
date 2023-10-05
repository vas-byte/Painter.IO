CPPFLAGS = -I/opt/homebrew/Cellar/sfml/2.6.0/include 
LDFLAGS = -L/opt/homebrew/Cellar/sfml/2.6.0/lib -lsfml-graphics -lsfml-window -lsfml-system
INCLUDE_PATH = /Implementations

default: main.cpp $(wildcard $(INCLUDE_PATH)/*.cpp)
	g++ $(CPPFLAGS) $(LDFLAGS) main.cpp Implementations/Bullet.cpp Implementations/Collectable.cpp Implementations/Game.cpp Implementations/Gun.cpp Implementations/Object.cpp Implementations/Person.cpp Implementations/Player.cpp Implementations/tileMap.cpp -o painter.IO

run: main.cpp $(wildcard $(INCLUDE_PATH)/*.cpp)
	make default
	./painter.IO