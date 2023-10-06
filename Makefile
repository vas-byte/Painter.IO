CPPFLAGS = -I/opt/homebrew/Cellar/sfml/2.6.0/include -I/opt/homebrew/Cellar/nlohmann-json/3.11.2/include
LDFLAGS = -L/opt/homebrew/Cellar/sfml/2.6.0/lib -lsfml-graphics -lsfml-window -lsfml-system
INCLUDE_PATH = /Implementations
CXXFLAGS = -std=c++17

default: main.cpp $(wildcard $(INCLUDE_PATH)/*.cpp)
	g++ $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) main.cpp Implementations/Bullet.cpp Implementations/Collectable.cpp Implementations/Game.cpp Implementations/Gun.cpp Implementations/Object.cpp Implementations/Person.cpp Implementations/Player.cpp Implementations/tileMap.cpp -o painter.IO

run: main.cpp $(wildcard $(INCLUDE_PATH)/*.cpp)
	make default
	./painter.IO