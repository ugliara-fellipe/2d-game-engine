CC=gcc
FLAGS=-Isrc -Igame -lSDL2

all: env main 

env:
	mkdir -p build

main: 
	${CC} src/engine.c game/main.c ${FLAGS} -o build/game

clean:
	rm -r -f build
