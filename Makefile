CPPFLAGS = -I/opt/homebrew/Cellar/sfml/2.6.0/include -I/opt/homebrew/Cellar/nlohmann-json/3.11.2/include
LDFLAGS = -L/opt/homebrew/Cellar/sfml/2.6.0/lib -lsfml-graphics -lsfml-window -lsfml-system
INCLUDE_PATH = /Implementations
CXXFLAGS = -std=c++17

#builds application (for running)
default: main.cpp $(wildcard $(INCLUDE_PATH)/*.cpp)
	g++ -g0 $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) main.cpp Implementations/HardBot.cpp Implementations/BotBehaviour.cpp Implementations/Ammo.cpp Implementations/Bullet.cpp Implementations/Collectable.cpp Implementations/Common.cpp Implementations/EasyBot.cpp Implementations/Game.cpp Implementations/Gun.cpp Implementations/Health.cpp Implementations/Object.cpp Implementations/Person.cpp Implementations/Player.cpp Implementations/tileFeature.cpp Implementations/Welcome.cpp Implementations/tileMap.cpp -o painter.IO

#builds & runs application
run: main.cpp $(wildcard $(INCLUDE_PATH)/*.cpp)
	make default
	./painter.IO

#builds application for testing memory leaks
leak: main.cpp $(wildcard $(INCLUDE_PATH)/*.cpp)
	g++ -g3 $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) main.cpp Implementations/HardBot.cpp Implementations/BotBehaviour.cpp Implementations/Ammo.cpp Implementations/Bullet.cpp Implementations/Collectable.cpp Implementations/Common.cpp Implementations/EasyBot.cpp Implementations/Game.cpp Implementations/Gun.cpp Implementations/Health.cpp Implementations/Object.cpp Implementations/Person.cpp Implementations/Player.cpp Implementations/tileFeature.cpp Implementations/tileMap.cpp -o painter.IO
	leaks --atExit -- ./painter.IO

test: Tests/tests.cpp $(wildcard $(INCLUDE_PATH)/*.cpp)
	g++ $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) Tests/tests.cpp Implementations/HardBot.cpp Implementations/BotBehaviour.cpp Implementations/Ammo.cpp Implementations/Bullet.cpp Implementations/Collectable.cpp Implementations/Common.cpp Implementations/EasyBot.cpp Implementations/Game.cpp Implementations/Gun.cpp Implementations/Health.cpp Implementations/Object.cpp Implementations/Person.cpp Implementations/Player.cpp Implementations/tileFeature.cpp Implementations/tileMap.cpp -o test
	./test
