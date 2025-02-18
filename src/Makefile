G++ = g++ -Wall -Werror -Wextra --std=c++17
GCC = gcc -Wall -Werror -Wextra
GCOV_FLAGS= -fprofile-arcs -ftest-coverage
OS := $(shell uname)

FRONT_DESKTOP = gui/desktop/snake/snake.pro
FRONT_CLI = gui/cli/*

BACK_DESKTOP = brick_game/snake/*
BACK_CLI = brick_game/tetris/* brick_game/snake/*

ifeq ($(OS), Linux)
		CHECK_FLAGS = -lcheck -lpthread -lsubunit -lrt -lm  
else
        CHECK_FLAGS = -lcheck 
endif

all: build
# @$(G++) main.cpp -o snake 
# ./snake
build: cli
cli:
	@$(G++) $(BACK_CLI) $(FRONT_CLI) main_cli.cpp -o brick_game_cli -lncurses -lrt

desktop:
	rm -rf build_dir
	mkdir build_dir
	@cd build_dir && qmake ../$(FRONT_DESKTOP)
	cd build_dir && make
	mv build_dir/snake .
	./snake
	

install: build
	@touch max_score.txt
	@echo 0 > max_score.txt
	@echo "Installation completed"
	@echo "'make run' to start the game"

run:
	./brick_game_cli

uninstall: clean
	rm -rf max_score.txt
	@echo "Uninstallation completed"


# desktop:
# 	rm -rf temp
# 	mkdir temp
# 	cd temp && qmake ../gui/desktop
# 	cd temp && make
# 	rm -rf temp
# 	./snake

test: clean
	$(GCC) tests/*.c $(BACK_CLI) -o test $(CHECK_FLAGS)
	./test

gcov_report: 
	$(GCC) tests/*.c $(BACK) -o test $(CHECK_FLAGS) $(GCOV_FLAGS) 
	./test
	rm -rf tests.gcda
	lcov -t "report" -o report.info --no-external -c -d .
	genhtml  -o ./report report.info
	rm -rf *.gcda *.gcno *.info

dvi:
	@cd docs && doxygen Doxyfile

dist:
	tar czf docs/tetris.tar.gz ../src Makefile ../README.md docs/Doxyfile

clang: 
	clang-format -n *.c brick_game/tetris/*.c brick_game/tetris/*.h gui/cli/*.c gui/cli/*.h tests/*.c tests/*.h

valgrind: test
	valgrind --tool=memcheck --leak-check=yes ./test

clean:
	@rm -rf *.gcda *.gcno *.info report
	@rm -rf ./test ./tetris max_score_tetris.txt max_score_snake.txt
	@rm -rf docs/html docs/latex docs/tetris.tar.gz
	rm -rf ./brick_game_cli 
	rm -rf build_dir ./snake

