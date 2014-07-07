CXX = clang
CFLAGS = -Wall -O0 -g
LIBS = -lstdc++ -lSDL -lGL
SRC = main.cpp
BIN = a

all:
	$(CXX) $(CFLAGS) $(LIBS) -o $(BIN) $(SRC)

.PHONY: emcc-setup
emcc-setup:
	. /d/lib/emscripten/init-emscripten-env.sh

emcc:
	emcc $(CFLAGS) $(LIBS) $(SRC) -o $(BIN).html

.PHONY: clean
clean:
	rm -f a a.js a.html a.html.map
