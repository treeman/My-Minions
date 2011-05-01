export CC=gcc
#speed add flags -O3 -minline-all-stringops
export CFLAGS=-c -Wno-unused-value -Wall -I./
export LIBS=-lX11 -lGL -lXrandr -lfreetype -lsndfile -lopenal -lpthread -lsfml-graphics-s -lsfml-audio -lsfml-window-s -lsfml-system-s -lboost_iostreams -llua

SRC=\
main.cpp \
Game.cpp \
IsoGrid.cpp \
World.cpp \
GameController.cpp \
Tile.cpp \
VisualObject.cpp \
Hero.cpp \
MoveableObject.cpp \
Intro.cpp \
Narrative.cpp \
Path.cpp \
PathObject.cpp \
ObjectFactory.cpp \
SimpleObjects.cpp

TREE_SRC=\
Tree/Game.cpp \
Tree/Util.cpp \
Tree/InputHandler.cpp \
Tree/Graphics.cpp \
Tree/Butler.cpp \
Tree/Sprite.cpp \
Tree/Timer.cpp \
Tree/Logo.cpp \
Tree/Tweaks.cpp \
Tree/Loghelper.cpp \
Tree/Rect.cpp \
Tree/VisualDebug.cpp \
Tree/Console.cpp \
Tree/Settings.cpp \
Tree/WindowManager.cpp \
Tree/GameDebug.cpp \
Tree/DrawnLazy.cpp

OBJ=$(SRC:.cpp=.o)
TREE_OBJ=$(TREE_SRC:.cpp=.o)
EXE=../bin/startme
DEBUG_EXE=../bin/startme-debug

.PHONY: all clean remake mrproper debug

all: $(SRC) $(TREE_SRC) $(EXE)

debug: $(SRC) $(TREE_SRC) $(DEBUG_EXE)

$(EXE): $(OBJ) $(TREE_OBJ)
	$(CC) $(OBJ) $(TREE_OBJ) -o $@ $(LIBS)

$(DEBUG_EXE): $(OBJ) $(TREE_OBJ)
	$(CC) $(OBJ) $(TREE_OBJ) -o $@ $(LIBS) -pg

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

remake: clean all

clean:
	rm -rf $(EXE) $(OBJ) $(DEBUG_EXE)

mrproper: clean
	rm -rf $(TREE_OBJ)

