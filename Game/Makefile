export CC=gcc
export CFLAGS=-c -Wno-unused-value -Wall -I../Tree/src
export LIBS=-lX11 -lGL -lXrandr -lfreetype -lsndfile -lopenal -lpthread -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lboost_iostreams -llua

SRC=\
main.cpp \
Demo.cpp

TREE_SRC=\
../Tree/src/Tree/Butler.cpp \
../Tree/src/Tree/Console.cpp \
../Tree/src/Tree/Game.cpp \
../Tree/src/Tree/GameDebug.cpp \
../Tree/src/Tree/Graphics.cpp \
../Tree/src/Tree/InputHandler.cpp \
../Tree/src/Tree/Loghelper.cpp \
../Tree/src/Tree/Logo.cpp \
../Tree/src/Tree/Rect.cpp \
../Tree/src/Tree/Settings.cpp \
../Tree/src/Tree/Debug.cpp \
../Tree/src/Tree/Sprite.cpp \
../Tree/src/Tree/Timer.cpp \
../Tree/src/Tree/Tweaks.cpp \
../Tree/src/Tree/Util.cpp \
../Tree/src/Tree/WindowManager.cpp

OBJ=$(SRC:.cpp=.o)
TREE_OBJ=$(TREE_SRC:.cpp=.o)
EXE=bin/startme

.PHONY: all clean remake mrproper

all: $(SRC) $(TREE_SRC) $(EXE)

$(EXE): $(OBJ) $(TREE_OBJ)
	$(CC) $(OBJ) $(TREE_OBJ) -o $@ $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

remake: clean all

clean:
	rm -rf $(EXE) $(OBJ)

mrproper: clean
	rm -rf $(TREE_OBJ)

