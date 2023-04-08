OS := $(shell uname -s)
CC = g++
FLAG = 
FLAG_C = -c 
CL_11 = -std=c++17 -Wall -Wextra -Werror
PR_NAME = MultiplayerPerceptron

ALL_FILE_CC = ./Model/ActivateFunctions/ActivateFunction.cpp ./Model/Graph/GraphNeuron.cpp ./Model/Graph/GraphPerceptron.cpp ./Model/Matrix/Matrix.cpp ./Model/Network/Network.cpp ./Controller/controller.cpp
ALL_FILE_H = ./Model/ActivateFunctions/ActivateFunction.h ./Model/Graph/GraphNeuron.h ./Model/Graph/GraphPerceptron.h ./Model/Matrix/Matrix.h ./Model/Network/Network.h ./Controller/controller.h

ifeq ($(OS), Darwin)
	FLAGS_PLATFORM = -lgtest
else
	FLAGS_PLATFORM = -lgtest -lsubunit -lrt -lm -lpthread -g
endif

all: clean $(PR_NAME).a

temp_test:
	@$(CC) $(PR_NAME).cc
	@./a.out

$(PR_NAME).a:
	@$(CC) $(FLAG_C) $(ALL_FILE_CC) $(ALL_FILE_H)
	@ar rcs $(PR_NAME).a $(ALL_FILE_O)

test: $(PR_NAME).a
	@$(CC) $(CL_11) ./test/test.cpp $(ALL_FILE_CC) -o tests.o -lgtest
	@./tests.o

gcov_report:
	@$(CC) --coverage $(ALL_FILE) ./test/test.cc $(FLAGS_PLATFORM) -o gov_report.o
	@./gov_report.o
	@lcov -t $(PR_NAME)_tests -o $(PR_NAME)_tests.info -c -d .
	@genhtml -o report $(PR_NAME)_tests.info
	@open ./report/index.html

install:
	@make clean
	@mkdir build
	@cd view && qmake && make && make clean && rm Makefile && cd ../ && mv view/view.app build/

uninstall:
	@rm -rf build*

dvi:
	open view/dvi.html

dist:
	rm -rf MLP/
	mkdir MLP/
	mkdir MLP/src
	mv  ./build/view.app  MLP/src/
	tar cvzf MLP.tgz MLP/
	rm -rf MLP/

clean:
	@rm -f *.a
	@rm -f *.o
	@rm -f *.out
	@rm -f *.gcda
	@rm -f *.gcdo
	@rm -f *.gcno
	@rm -f *.info
	@rm -f *.info
	@rm -f ./*/*.gch
	@rm -f ./*/*/*.gch
	@rm -rf build
	@rm -f RESULT_VALGRIND.txt

check:
	@cd view && clang-format -i *.cpp *.h
	@cd Model && clang-format -i ./ActivateFunctions/ActivateFunction.cpp ./Graph/GraphNeuron.cpp ./Graph/GraphPerceptron.cpp ./Matrix/Matrix.cpp ./Network/Network.cpp
	@cd Controller && clang-format -i *.cpp *.h
  
	@cd view && clang-format -n *.cpp *.h
	@cd Model && clang-format -n ./ActivateFunctions/ActivateFunction.cpp ./Graph/GraphNeuron.cpp ./Graph/GraphPerceptron.cpp ./Matrix/Matrix.cpp ./Network/Network.cpp
	@cd Controller && clang-format -n *.cpp *.h

cppcheck:  
    @cppcheck --enable=all --suppress=missingIncludeSystem $(ALL_FILE_CC)
