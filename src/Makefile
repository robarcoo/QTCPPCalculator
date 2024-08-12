.PHONY: all test clean

CFLAGS= -std=c++17 -Wall -Wextra -Werror -g 
SRC= model/calc.cc model/mcredit.cc model/parser.cc model/rpn.cc model/validate.cc
GCOVFLAGS=-fprofile-arcs -ftest-coverage
LFLAGS=-lgcov --coverage
TEST_LIBS=-lgtest -lpthread
CC= g++

ifeq ($(shell uname), Linux)
	FILE_PATH = ./view
endif
ifeq ($(shell uname), Darwin)
	FILE_PATH = ./install/view.app/Contents/MacOS/view
endif


all: clean test

test: clean
	$(CC) $(CFLAGS) $(GCOVFLAGS) $(SRC) model/tests.cc -o test_calc $(TEST_LIBS) -fsanitize=address
	./test_calc

install:
	mkdir build
	cd view/view && qmake && make && make clean && cp -r $(FILE_PATH) ../../build

uninstall:
	rm -rf build

gcov_report: test
	lcov -t "./test" -o test.info --no-external -c -d ./
	genhtml -o report test.info
	open report/index.html

format:
	clang-format -i -style=google model/*.cc model/*.h controller/*.cc controller/*.h
	clang-format -n -style=google model/*.cc model/*.h controller/*.cc controller/*.h

dvi:
	open dvi.md

dist:
	mkdir Archive_SmartCalc_v2.0
	cp -a build/* Archive_SmartCalc_v2.0
	tar -cvzf Archive_SmartCalc_v2.0.tar.gz Archive_SmartCalc_v2.0
	rm -rf Archive_SmartCalc_v2.0



clean:
	rm -rf *.o *.a *.so *.gcda *.gcno *.gch rep.info *.html *.css *.exe *.dSYM *.info test_calc report/ .DS_Store ../.DS_Store .clang-format
	rm -rf Archive_SmartCalc_v2.0 gcov
	rm -rf *gz
 
