
CXX = g++
CXXFLAGS = -g -std=c++11 -Wall 
LDFLAGS = -lallegro -lallegro_main \
    -lallegro_color -lallegro_font -lallegro_ttf -lallegro_acodec -lallegro_audio -lallegro_primitives -lallegro_image

all: main

main.o: main.cpp geom.hpp geom.hpp init.hpp ai.hpp
tela.o: tela.cpp tela.hpp geom.hpp 
draw.o: draw.cpp draw.hpp tela.cpp tela.hpp geom.hpp
physics.o: physics.cpp physics.hpp
ai.o: ai.cpp ai.hpp

main: main.o tela.o draw.o physics.o ai.o
	$(CXX) $(CXXFLAGS) -o $@  $^ $(LDFLAGS)

clean:
	rm -f main *.o
