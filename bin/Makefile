#!/bin/bash
#ubuntu
#sudo apt-get install freeglut3-dev
#mac
#brew install freeglut

SRC_DIR=../src
LIB_DIR=../lib
INC_DIR=../include


COMPILER=g++
FLAGS=-O -Wno-deprecated-declarations -I $(INC_DIR) -L $(LIB_DIR)
LIBS=
POSTPROC=

ifeq ($(os),Windows_NT)
	#FIGURE OUT WINDOWS
else
	ifeq ($(shell uname),Darwin)
		LIBS+=-framework OpenGL -framework GLUT -lirrklang
		POSTPROC=install_name_tool -change /usr/local/lib/libirrklang.dylib $(LIB_DIR)/libirrklang.dylib $@
	else
		LIBS+=-lGL -lGLU -lglut $(LIB_DIR)/libIrrKlang.so
	endif
endif

GAME_SRC=$(SRC_DIR)/game.cpp $(SRC_DIR)/classes.cpp
GRAPHIC_SRC=$(SRC_DIR)/spritelib/spritelib.cpp $(SRC_DIR)/spritelib/spritelib_anim.cpp $(SRC_DIR)/spritelib/spritelib_text.cpp

all: zombies

zombies: $(GAME_SRC) $(GRAPHIC_SRC)
	$(COMPILER) $^ $(FLAGS) $(LIBS) -o $@
	$(POSTPROC)

clean:
	@rm -rf zombies zombies.exe
