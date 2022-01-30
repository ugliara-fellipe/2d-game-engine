CC=gcc
FLAGS=-Isrc -Igame -lSDL2 -lm -lSDL2_ttf

SRC=src/assets/assets.c src/entity/entity.c src/entity/aspect.c \
    src/draw/text.c src/draw/tile.c \
	src/draw/sprite.c src/draw/tilegroup.c src/engine/engine.c \
	src/engine/monitor.c src/engine/timing.c src/toolbelt/vector2d.c \
	src/toolbelt/maths.c game/main.c

all: env main 

env:
	mkdir -p build

main: 
	${CC} ${SRC} ${FLAGS} -o build/game

clean:
	rm -r -f build
