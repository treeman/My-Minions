export CC=gcc
export CFLAGS=-c -Wall -I../Tree/src
export LIBS=-lX11 -lGL -lXrandr -lfreetype -lsndfile -lopenal -lpthread -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lboost_iostreams -llua

SRC=\
Demo.cpp \
main.cpp \
../Tree/src/Tree/Butler.cpp \
../Tree/src/Tree/Console.cpp \
../Tree/src/Tree/Game.cpp \
../Tree/src/Tree/GameDebug.cpp \
../Tree/src/Tree/Graphics.cpp \
../Tree/src/Tree/InputHandler.cpp \
../Tree/src/Tree/Loghelper.cpp \
../Tree/src/Tree/Logo.cpp \
../Tree/src/Tree/Log.cpp \
../Tree/src/Tree/Rect.cpp \
../Tree/src/Tree/Settings.cpp \
../Tree/src/Tree/Sprite.cpp \
../Tree/src/Tree/Timer.cpp \
../Tree/src/Tree/Tweaks.cpp \
../Tree/src/Tree/Util.cpp \
../Tree/src/Tree/Vec2D.cpp \
../Tree/src/Tree/WindowManager.cpp

OBJ=$(SRC:.cpp=.o)
EXE=bin/startme

.PHONY: all clean

all: $(SRC) $(EXE)

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf ../obj/* $(OBJ) $(EXE)
