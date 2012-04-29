#Just construct the project with one line
all:
	g++ src/*.cpp -lm -lGL -lGLU -lalut -lopenal -logg -lvorbisfile -lSDL -lcorona -lpng -ljpeg -o GWAIN
clean:
	rm *.o GWAIN
