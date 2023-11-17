all : bin/test bin/exemple bin/affichage
bruit : bin/bruit

bin/bruit : obj/mainBruit.o obj/Image.o obj/Pixel.o
	g++ -g obj/mainBruit.o obj/Image.o obj/Pixel.o -o bin/bruit -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer -lGL

bin/exemple : obj/mainExemple.o obj/Image.o obj/Pixel.o
	g++ -g obj/mainExemple.o obj/Image.o obj/Pixel.o -o bin/exemple -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer -lGL
	
bin/test : obj/mainTest.o obj/Image.o obj/Pixel.o
	g++ -g obj/mainTest.o obj/Image.o obj/Pixel.o -o bin/test -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer -lGL

bin/affichage : obj/mainAffichage.o obj/Image.o obj/Pixel.o
	g++ -g obj/mainAffichage.o obj/Image.o obj/Pixel.o -o bin/affichage -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer -lGL

obj/mainBruit.o : src/mainBruit.cpp src/Image.h
	g++ -g -Wall -o obj/mainBruit.o -c src/mainBruit.cpp -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer -lGL

obj/mainExemple.o : src/mainExemple.cpp src/Image.h
	g++ -g -Wall -o obj/mainExemple.o -c src/mainExemple.cpp -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer -lGL

obj/mainTest.o : src/mainTest.cpp src/Image.h
	g++ -g -Wall -o obj/mainTest.o -c src/mainTest.cpp -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer -lGL

obj/mainAffichage.o : src/mainAffichage.cpp src/Image.h
	g++ -g -Wall -o obj/mainAffichage.o -c src/mainAffichage.cpp -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer -lGL



obj/Image.o : src/Image.cpp src/Image.h src/Pixel.h
	g++ -g -Wall -o obj/Image.o -c src/Image.cpp -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer -lGL
	
obj/Pixel.o : src/Pixel.cpp src/Pixel.h 
	g++ -g -Wall -o obj/Pixel.o -c src/Pixel.cpp -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer -lGL


clean:
	rm -rf obj/*.o bin/* doc/latex data/*

