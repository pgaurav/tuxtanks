CC=g++
SRC=main.cpp \
    texture.cpp \
    font.cpp \
    button.cpp \
    textbox.cpp \
    listbox.cpp \
    radio.cpp \
    tank.cpp \
    audio.cpp \
    welcomeanim.cpp \
    introanim.cpp 
LIB=-lSDL -lSDL_mixer -lSDL_image -lGL -lGLU -lftgl
INC=-I/usr/include/freetype2

all:
	$(CC) -g3 $(SRC) $(INC) $(LIB)

clean:
	rm -rf *~ *.o a.out
