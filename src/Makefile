CC = g++ -Wall -Werror -Wextra -std=c++17
GTESTFLAG = -lgtest

SRC_BACK_DIR = $(wildcard back/*.cc)
SRC_CONTROLLER_DIR = $(wildcard controller/s21_*.cc)
ALL_FILES = $(SRC_BACK_DIR) $(SRC_CONTROLLER_DIR)

SRC_FRONT_DIR = front
QT_PROJECT_NAME = 3dviewer
QT_PROJECT_FOLDER = ./$(SRC_FRONT_DIR)
QT_PRO = $(QT_PROJECT_NAME).pro
QT_MAKEFILE = $(QT_PROJECT_NAME)_Makefile
QT_BUILD_FOLDER = build
QT_APP_FOLDER = ../App
DIST_FOLDER_NAME = 3DVIEWER_V2
TAR_DIR = $(QT_PROJECT_NAME)_Archive

OS_NAME = $(shell uname -s)
TAR_DIR = Viewer.0_Archive

ifeq ($(OS_MAME), Linux)
	LFLAGS += -lrt -lsubunit -lm
endif

all: test install

install: generate_make
	@echo "Building application..."
	cd ./$(QT_BUILD_FOLDER) && make -s -f $(QT_MAKEFILE)
	@echo "Application builded."
	@echo  "Moving application to folder \"$(QT_APP_FOLDER)\"..." -n
	mkdir -p ./$(QT_APP_FOLDER)
ifeq ($(OS_NAME), Linux) 
	mv build/$(QT_PROJECT_NAME) ../App 
endif 
ifeq ($(OS_NAME), Darwin)
	mv build/$(QT_PROJECT_NAME).app ../App 
endif
	@echo "Done."
	@echo "Deleting build folder..."
	rm -rf $(QT_BUILD_FOLDER)
	@echo "Done."
	@echo "Installation complete!"

generate_make:
	qmake $(QT_PROJECT_FOLDER)/$(QT_PRO) -o ./$(QT_BUILD_FOLDER)/$(QT_MAKEFILE)
	rm -rf .qmake.stash

uninstall:
	@echo "Uninstalling application..."
	rm -rf $(QT_APP_FOLDER)
	@echo "Done"

dist:
	rm -Rf $(TAR_DIR)
	mkdir $(TAR_DIR)
	mkdir $(TAR_DIR)/src
	cp -R  front $(TAR_DIR)/src
	cp -R  back $(TAR_DIR)/src
	cp -R  controller $(TAR_DIR)/src
	cp -R  gifLib $(TAR_DIR)/src
	cp -R  Doxyconf Makefile $(TAR_DIR)/src
	tar cvzf $(TAR_DIR).tgz $(TAR_DIR)
	mv $(TAR_DIR).tgz ..
	rm -Rf $(TAR_DIR)

dvi:
	doxygen Doxyconf
	open documentations/html/index.html

style:
	clang-format -style=Google -n back/*.cc back/*.h
	clang-format -style=Google -n front/*.cc front/*.h
	clang-format -style=Google -n controller/*.cc controller/*.h

test: $(ALL_FILES)
	$(CC) $(FLAGS) $(ALL_FILES) $(GTESTFLAG) -o test -lpthread
	./test

clean:
	rm -rf *.o
	rm -f test
	rm -f Viewer.0_Archive