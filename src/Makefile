CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
OBJ_DIR = obj
GCOV_DIR = gcov
PROJECT_NAME = s21_string
TEST_SRC = $(PROJECT_NAME)_test.c
LIB_SRC_DIR = functions
TEST_BIN = $(OBJ_DIR)/tests/s21_string_test
OS := $(shell uname -s)
LIB_SOURCES = $(shell find $(LIB_SRC_DIR) -name '*.c')
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(LIB_SOURCES))
HS = $(shell find . -name '*.h')
TEST_FLAGS = -lcheck

ifeq ($(OS), Darwin)
	OPEN_CMD = open
	ADD_FLAGS =
endif

ifeq ($(OS), Linux)
	OPEN_CMD = xdg-open
	ADD_FLAGS = -lrt -lpthread -lm -lsubunit
endif

all: clean gcov_report

$(OBJ_DIR)/%.o: %.c $(HS)
	$(CC) $(CFLAGS) $(ADD_FLAGS) -I . $< -c -o $@

create_obj_files: $(OBJS)

$(PROJECT_NAME).a: create_obj_files
	ar rcs $@ $(OBJ_DIR)/$(LIB_SRC_DIR)/*.o
	ranlib $@

test: $(TEST_SRC) $(PROJECT_NAME).a
	$(CC) $(CFLAGS) $^ -o $(TEST_BIN) $(TEST_FLAGS) $(ADD_FLAGS)
	@echo s21_string: Check leaks
ifeq ($(OS), Linux)
	valgrind --tool=memcheck --vgdb=no --trace-children=yes --log-file=RESULT_VALGRIND.log ./$(TEST_BIN)
	tail -n 9 RESULT_VALGRIND.log
else
	leaks -quiet --atExit -- ./$(TEST_BIN)
endif

add_report_flags:
	$(eval CFLAGS += -fprofile-arcs -ftest-coverage -fPIC)
	@echo s21_stringplus: Check build

gcov_report: clean add_report_flags test
	gcov *.c -o ${LIB_SRC_DIR}/*.c -o $(OBJ_DIR)/*
	mv *.gc* ./gcov/
	mv $(OBJ_DIR)/*/*.gc* ./gcov/
	lcov -t gcov/ -o report.info -c -d gcov/
	genhtml -o report report.info
	$(OPEN_CMD) ./report/index.html

clang:
	cp ../materials/linters/.clang-format .
	clang-format -n $(LIB_SRC_DIR)/*.c
	clang-format -n $(LIB_SRC_DIR)/*.h
	clang-format -n *.c *.h

clang-replace:
	cp ../materials/linters/.clang-format .
	clang-format -i $(LIB_SRC_DIR)/*.c
	clang-format -i *.c *.h
	clang-format -i $(LIB_SRC_DIR)/*.h

install:
	cd ~
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install lcov
	brew install gcovr

clear:
	clear

clean:
	rm -rf *.info
	rm -rf report/
	rm -rf *.dSYM
	rm -rf *.a
	rm -rf RESULT_VALGRIND.log
	rm -rf $(GCOV_DIR)/*
	rm -rf $(OBJ_DIR)/$(LIB_SRC_DIR)/*.o
	rm -rf $(TEST_BIN)
	clear

.PHONY: test gcov_report clean all $(PROJECT_NAME).a add_report_flags clang clang-replace
