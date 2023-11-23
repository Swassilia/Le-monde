all : bin/bruit 
bruit : bin/bruit

obj : mkdir -p obj/

bin : mkdir -p bin/

bin/bruit : obj/mainBruit.o obj/Image.o obj/Pixel.o
	g++ -g obj/mainBruit.o obj/Image.o obj/Pixel.o -o bin/bruit -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer -lGL


obj/mainBruit.o : src/mainBruit.cpp src/Image.h
	g++ -g -Wall -o obj/mainBruit.o -c src/mainBruit.cpp -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer -lGL


obj/Image.o : src/Image.cpp src/Image.h src/Pixel.h
	g++ -g -Wall -o obj/Image.o -c src/Image.cpp -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer -lGL
	
obj/Pixel.o : src/Pixel.cpp src/Pixel.h 
	g++ -g -Wall -o obj/Pixel.o -c src/Pixel.cpp -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer -lGL


clean:
	rm -rf obj/*.o bin/* doc/latex data/*

