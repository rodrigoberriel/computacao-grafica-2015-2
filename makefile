all:
	g++ -std=c++11 main.cpp XML.cpp tinyxml2.cpp Arena.cpp Circle.cpp EstruturasBasicas.cpp Rect.cpp SVG.cpp Helicoptero.cpp Tiro.cpp imageloader.cpp -o trabalhocg -lGL -lGLU -lglut 

valgrind:
	g++ -g -std=c++11 main.cpp XML.cpp tinyxml2.cpp Arena.cpp Circle.cpp EstruturasBasicas.cpp Rect.cpp SVG.cpp Helicoptero.cpp Tiro.cpp imageloader.cpp -o trabalhocg -lGL -lGLU -lglut 

clean:
	rm -rf trabalhocg
