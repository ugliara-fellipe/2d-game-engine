CC=gcc
FLAGS=-Isrc -lSDL2 -lm -lSDL2_ttf -lSDL2_mixer -lSDL2_image -lSDL2_gfx

ENGINE=src/assets/assets.c src/entity/entity.c src/entity/aspect.c \
    src/draw/text.c src/draw/tile.c src/audio/music.c src/audio/sound.c\
	src/draw/sprite.c src/draw/tilegroup.c src/engine/engine.c \
	src/engine/monitor.c src/engine/timing.c src/toolbelt/vector2d.c \
	src/toolbelt/maths.c src/toolbelt/shape.c src/draw/graphics.c \
	src/collision/collision.c

GAME_ONE=game/one/level.c game/one/player.c game/one/main.c

GAME_TWO=game/two/scene/world/level.c game/two/scene/world/camera.c \
    game/two/actor/player/control.c game/two/actor/trajectory.c \
	game/two/scene/world/local/outpost.c game/two/actor/player/player.c \
	game/two/object/world/door.c game/two/main.c game/two/context.c \
	game/two/scene/menu/menu.c game/two/scene/menu/station.c \
	game/two/scene/menu/charsheet.c game/two/scene/world/world.c \
	game/two/scene/menu/badges.c game/two/scene/menu/begin.c \
	game/two/object/world/ladder.c game/two/object/world/gate.c

all: env main 

env:
	mkdir -p build

main: 
	${CC} ${ENGINE} ${GAME_ONE} ${FLAGS} -Igame/one -o build/gameone
	${CC} ${ENGINE} ${GAME_TWO} ${FLAGS} -Igame/two -o build/gametwo

clean:
	rm -r -f build
