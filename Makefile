NAME = gomoku

BUILD_FOLDER = build/

SRC_FOLDER = src/

all:
	if [ ! -d $(BUILD_FOLDER) ];then \
		mkdir -p build; \
	fi

	cmake -B$(BUILD_FOLDER) -H$(SRC_FOLDER)
	make -C build
	rsync $(BUILD_FOLDER)/$(NAME) .

clean:
	if [ -d $(BUILD_FOLDER) ];then \
		make -C build clean; \
		rm -rf $(NAME); \
	fi

fclean:
	rm -rf build
	rm -rf $(NAME)

re: fclean all

.SILENT: