CC=gcc
FLAGS=-Isrc -Igame -lSDL2 -lm -lSDL2_ttf

all: env main 

env:
	mkdir -p build

main: 
	${CC} src/assets/assets.c src/draw/text.c src/draw/tile.c src/engine/engine.c src/engine/monitor.c src/engine/timing.c src/toolbelt/vector2d.c src/toolbelt/maths.c game/main.c ${FLAGS} -o build/game

clean:
	rm -r -f build
