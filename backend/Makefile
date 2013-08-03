INC_DIR = inc/

CXX_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CXX_FILES:.cpp=.o)))

DEP_FILES := $(addprefix dep/,$(notdir $(OBJ_FILES:.o=.d)))

CFLAGS = -g -std=c++11 -Wl,--no-as-needed -Wall -I $(INC_DIR)
CXX = g++
RCXX = $(CFLAGS) $(ROOTCFLAGS)

MKDIR_P = mkdir -p

OBJ_MAIN := $(OBJ_FILES) obj/main.o
CXX_MAIN := $(CXX_FILES) main.cpp
DEP_MAIN := $(DEP_FILES) dep/main.d

all: directories $(OBJ_MAIN)
	$(CXX) -Wl,--no-as-needed $(OBJ_MAIN) -o ../StatGen.cgi
	@echo '-> StatGen.cgi created!'

obj/%.o: src/%.cpp
	$(CXX) $(RCXX) -MD -MF $(patsubst obj/%.o,dep/%.d,$@) -c -o $@ $<

obj/main.o: main.cpp
	$(CXX) $(RCXX) -MD -MF dep/main.d -c -o obj/main.o main.cpp

directories:
	@${MKDIR_P} obj/
	@${MKDIR_P} dep/

-include $(DEP_MAIN)

clean:
	@rm -f *~
	@rm -f obj/*.o
	@rm -f dep/*.d
	@rm -f *.x
