CC=clang++
LD=clang++
LIBS=-lSDL2
CFLAGS=--std=c++14 -Wall -O2
LDFLAGS=--std=c++14 -O2 -s $(LIBS)
#CFLAGS=--std=c++14 -Wall -O2 -g
#LDFLAGS=--std=c++14 -O2 -g $(LIBS)
EXE=shooter
SRC=$(wildcard src/*.cpp)
OBJS=$(addprefix build/,$(notdir $(SRC:.cpp=.o)))

$(EXE): $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXE)

build/%.o: src/%.cpp
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o build/$(notdir $(<:.cpp=.o))

.PHONY: clean
clean:
	rm -r build $(EXE)
