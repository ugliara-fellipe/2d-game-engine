CC=gcc
FLAGS=-Isrc -Igame -lSDL2 -lm -lSDL2_ttf -lSDL2_mixer -lSDL2_image -lSDL2_gfx

SRC=src/assets/assets.c src/entity/entity.c src/entity/aspect.c \
    src/draw/text.c src/draw/tile.c src/audio/music.c src/audio/sound.c\
	src/draw/sprite.c src/draw/tilegroup.c src/engine/engine.c \
	src/engine/monitor.c src/engine/timing.c src/toolbelt/vector2d.c \
	src/toolbelt/maths.c src/toolbelt/shape.c src/draw/graphics.c \
	src/collision/collision.c game/level.c game/player.c game/main.c

all: env main 

env:
	mkdir -p build

main: 
	${CC} ${SRC} ${FLAGS} -o build/game

clean:
	rm -r -f build
