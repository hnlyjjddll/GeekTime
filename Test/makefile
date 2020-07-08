CC = gcc
CXX = g++
MYFLAGS = -std=c++11 -Wall

INC += \
	-I /mnt/f/study/3rd/googletest/googlemock/include \
	-I /mnt/f/study/3rd/googletest/googletest/include \

LIB += -lgtest \
        -lgtest_main \
        -lpthread

TAR_DIR = ./bin
SRC_DIR = ./src
OBJ_DIR = ./obj
BIN_TARGET = $(TAR_DIR)/unit_test

BIN_TARGET_OBJS = \
		$(OBJ_DIR)/unit_test.o	\

all: init $(BIN_TARGET)
	@echo -e "\033[1;32m\nSuccess!\033[0m"
	ldd -r $(BIN_TARGET)

$(BIN_TARGET): $(BIN_TARGET_OBJS)
	@echo -e "\033[1;33m\nLinking $< ==> $@\033[0m"
	$(CXX) $(MYFLAGS) $^ -o $@ $(LIB)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo -e "\033[1;33m\nCompiling $< ==> $@\033[0m"
	$(CXX) $(MYFLAGS) -c -o $@ $(INC) $<
clean:
	rm -f  $(BIN_TARGET_OBJS) $(BIN_TARGET)
init:
	mkdir -p $(sort ./ $(TAR_DIR) $(SRC_DIR) $(OBJ_DIR) )