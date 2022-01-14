CC=gcc
FLAGS=-Isrc -Igame -lSDL2 -lm

all: env main 

env:
	mkdir -p build

main: 
	${CC} src/engine.c src/toolbelt/vector2d.c src/toolbelt/maths.c game/main.c ${FLAGS} -o build/game

clean:
	rm -r -f build
