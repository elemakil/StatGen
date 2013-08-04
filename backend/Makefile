INC_DIR = inc/
BINARY = ../StatGen.cgi
BINARY_LINK = ../index.cgi

CXX_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CXX_FILES:.cpp=.o)))
DEP_FILES := $(addprefix dep/,$(notdir $(OBJ_FILES:.o=.d)))

CXX_TESTING_FILES := $(wildcard testing/*.cpp)
OBJ_TESTING_FILES := $(addprefix obj/,$(notdir $(CXX_TESTING_FILES:.cpp=.o)))
DEP_TESTING_FILES := $(addprefix dep/,$(notdir $(OBJ_TESTING_FILES:.o=.d)))

CFLAGS = -g -std=c++0x -Wl,--no-as-needed -Wall -I $(INC_DIR)
LFLAGS = -Wl,--no-as-needed
CXX = g++
RCXX = $(CFLAGS) $(ROOTCFLAGS)

MKDIR_P = mkdir -p

OBJ_MAIN := $(OBJ_FILES) obj/main.o
CXX_MAIN := $(CXX_FILES) main.cpp
DEP_MAIN := $(DEP_FILES) dep/main.d

all: directories $(OBJ_MAIN)
	$(CXX) $(LFLAGS) $(OBJ_MAIN) -o $(BINARY)
	@ln -s $(notdir $(BINARY)) $(BINARY_LINK)
	@echo ''
	@echo '##################################################'
	@echo '#          -> StatGen.cgi created!               #'
	@echo '##################################################'

test: directories $(OBJ_FILES) $(OBJ_TESTING_FILES)
	@echo ' -> Linking the testing code!'
	@$(foreach OBJ_THIS_TEST,$(OBJ_TESTING_FILES), $(CXX) $(LFLAGS) $(OBJ_FILES) $(OBJ_THIS_TEST) -o $(addprefix bin/,$(notdir $(OBJ_THIS_TEST:.o=.x))); echo ' --> Testing case "$(notdir $(OBJ_THIS_TEST:.o=))" created!';)

obj/%.o: testing/%.cpp
	$(CXX) $(RCXX) -MD -MF $(patsubst obj/%.o,dep/%.d,$@) -c -o $@ $<

obj/%.o: src/%.cpp
	$(CXX) $(RCXX) -MD -MF $(patsubst obj/%.o,dep/%.d,$@) -c -o $@ $<

obj/main.o: main.cpp
	$(CXX) $(RCXX) -MD -MF dep/main.d -c -o obj/main.o main.cpp

directories:
	@${MKDIR_P} obj/
	@${MKDIR_P} dep/
	@${MKDIR_P} bin/
	@${MKDIR_P} data/

-include $(DEP_MAIN)

clean:
	@rm -f *~
	@rm -f obj/*.o
	@rm -f dep/*.d

veryclean: clean
	@rm -f *.x
	@rm -f bin/*.x
	@rm -f $(BINARY)
