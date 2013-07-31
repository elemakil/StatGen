INC_DIR = inc/

CXX_FILES := $(wildcard src/*.cxx)
OBJ_FILES := $(addprefix obj/,$(notdir $(CXX_FILES:.cxx=.o)))

DEP_FILES := $(addprefix dep/,$(notdir $(OBJ_FILES:.o=.d)))

CFLAGS = -g -std=c++11 -Wl,--no-as-needed -Wall -I $(INC_DIR)
CXX = g++
RCXX = $(CFLAGS) $(ROOTCFLAGS)

OBJ_MAIN := $(OBJ_FILES) obj/main.o
CXX_MAIN := $(CXX_FILES) main.cxx
DEP_MAIN := $(DEP_FILES) dep/main.d

all: $(OBJ_MAIN)
	$(CXX) -Wl,--no-as-needed $(OBJ_MAIN) -o main.x
	@echo '-> main.x created!'

obj/%.o: src/%.cxx
	$(CXX) $(RCXX) -MD -MF $(patsubst obj/%.o,dep/%.d,$@) -c -o $@ $<

obj/main.o: main.cxx
	$(CXX) $(RCXX) -MD -MF dep/main.d -c -o obj/main.o main.cxx


-include $(DEP_MAIN)

clean:
	@rm -f *~
	@rm -f obj/*.o
	@rm -f dep/*.d
	@rm -f tmp/*.o
	@rm -f *.x
