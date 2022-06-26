# Name of the project
PROJ_NAME=game
 
# .c files
C_SOURCE=$(wildcard ./src/*.cpp)
 
# .h files
H_SOURCE=$(wildcard ./include/*.hpp)
 
# objects
OBJ=$(subst .cpp,.o,$(subst src,objects,$(C_SOURCE)))
 
# Flags for compiler
CC_FLAGS= -lsfml-graphics -lsfml-window -lsfml-system

all: build run

build: ${OBJ}
	@ mkdir -p build
	-g++ $^ -o build/${PROJ_NAME} ${CC_FLAGS}

./objects/%.o: ./src/%.cpp ./include/%.hpp
	@ mkdir -p objects
	-g++ -o $@ $< $(CC_FLAGS)
 
./objects/main.o: ./src/main.cpp
	@ mkdir -p objects
	-g++ -c $< -o $@ $(CC_FLAGS) -I ./include

test:
	g++ -c src/main.cpp -o objects/main.o

	g++ objects/main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network
run:
	@ ./build/${PROJ_NAME}

clean:
	rm -f ./objects/*.o