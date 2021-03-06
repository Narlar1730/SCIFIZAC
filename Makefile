# optional flags (if the compiler supports it)
CXXFLAGS += -std=c++11

# HIGHLY RECOMMENDED flags
CXXFLAGS += -Wall -Wextra -pedantic-errors -lsfml-graphics -lsfml-window -lsfml-system

# Include the headers
HEADERS := $(wildcard *.h)

# required for SFML programs
LDLIBS := $(shell pkg-config sfml-all --libs)
LDLIBS += -lX11
# The rest will turn any source file ending in .cpp
# into a program of the same name

SOURCES := $(wildcard *.cpp)
PROGRAMS := $(patsubst %.cpp,%,$(SOURCES))

all: $(PROGRAMS)

clean:
	$(RM) $(PROGRAMS)
