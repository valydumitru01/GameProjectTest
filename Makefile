all:
	g++ -I ./src/include -L ./src/bin -o ./Builds/Win_Build/engine main.cpp -lmingw32 -lSDL2main -lSDL2  -lmingw32 -lopengl32 -lglew32 -lglew32mx -lglu32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf --verbose