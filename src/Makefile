G++ = g++ -Wall -Werror -Wextra --std=c++17
GCC = gcc -Wall -Werror -Wextra
GCOV_FLAGS= -fprofile-arcs -ftest-coverage
GTEST = -lgtest -lpthread
OS := $(shell uname)

FRONT_DESKTOP = gui/desktop/desktop.pro
FRONT_CLI = gui/cli/*

BACK_DESKTOP = brick_game/snake/*
BACK_CLI = brick_game/tetris/* brick_game/snake/*

ifeq ($(OS), Linux)
		CHECK_FLAGS = -lcheck -lpthread -lsubunit -lrt -lm  
else
        CHECK_FLAGS = -lcheck 
endif

all: install test dvi dist

install: cli desktop
	@echo "'make run_cli' or 'make run_desktop' to start the game"

cli:
	@touch max_score_tetris.txt
	@echo 0 > max_score_tetris.txt
	@$(G++) $(BACK_CLI) $(FRONT_CLI) main_cli.cpp -o cli -lncurses -lrt 

desktop:
	@rm -rf build_dir
	@mkdir build_dir
	@touch max_score_snake.txt
	@echo 0 > max_score_snake.txt
	@cd build_dir && qmake ../$(FRONT_DESKTOP) 
	@cd build_dir && make
	@mv build_dir/desktop .

run_desktop:
	./desktop

run_cli:
	./cli

uninstall: clean

test: test_tetris test_snake gcov_report

test_tetris: 
	$(GCC) tests_tetris/*.c brick_game/tetris/*.c -o test_tetris $(CHECK_FLAGS) $(GCOV_FLAGS) 
	./test_tetris

test_snake:
	$(G++) tests_snake/test_*.cpp brick_game/snake/*.cpp -o test_snake $(GTEST) $(GCOV_FLAGS) 
	./test_snake

gcov_report:
	lcov -t "TetrisCoverage" -o tetris_coverage.info --no-external -c -d .
	lcov -t "SnakeCoverage" -o snake_coverage.info --no-external -c -d .
	lcov -a tetris_coverage.info -a snake_coverage.info -o total_coverage.info
	genhtml -o ./gcov_report total_coverage.info
	rm -rf *.gcda *.gcno tetris_coverage.info snake_coverage.info total_coverage.info coverage_tetris coverage_snake

dvi:
	@cd docs && doxygen Doxyfile

dist:
	tar czf docs/brick_game.tar.gz ../src Makefile ../README.md docs/Doxyfile

clang: 
	clang-format -n brick_game/tetris/*.c brick_game/tetris/*.h brick_game/snake/*.h brick_game/*.h brick_game/snake/*.cpp gui/cli/*.c gui/cli/*.h gui/desktop/*.cpp gui/desktop/*.h tests_tetris/*.c tests_tetris/*.h tests_snake/*.cpp tests_snake/*.h main_cli.cpp

valgrind: test
	valgrind --tool=memcheck --leak-check=yes ./test_snake ./test_tetris

clean:
	@rm -rf *.gcda *.gcno *.info ./gcov_report coverage_tetris coverage_snake
	@rm -rf ./snake ./tetris max_score_tetris.txt max_score_snake.txt ./test_snake ./test_tetris
	@rm -rf docs/html docs/latex docs/brick_game.tar.gz
	@rm -rf build_dir ./desktop gui/build-desktop-Desktop-Debug ./cli 

