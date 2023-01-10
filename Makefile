COMPILER = clang++
DEBUG_RB_TREE= -DDEBUG_RED_BLACK_TREE
FLAGS_DEBUG = --std=c++98 -Wall -Wextra -Werror -g #-fsanitize=address $(DEBUG_RB_TREE)
FLAGS = --std=c++98 -Wall -Wextra -Werror

VECTOR=vector
MAP=map
STACK=stack
SET=SET
RD_TREE=rd_tree

all: $(VECTOR))
	cp $(MAP) a.out

$(VECTOR):
	@$(COMPILER) $(FLAGS_DEBUG)	src/vector/Vector_tests.cpp -o $(VECTOR)

$(MAP):
	@$(COMPILER) $(FLAGS_DEBUG)	src/map/Map_tests.cpp -o $(MAP)

$(STACK):
	@$(COMPILER) $(FLAGS_DEBUG)	src/stack/Stack_tests.cpp -o $(STACK)
$(RD_TREE): fclean
	@$(COMPILER) $(FLAGS_DEBUG)	src/red-black-tree/RedBlackTreeTests.cpp -o $(RD_TREE)
#set: $(SET)
#	@$(COMPILER) $(FLAGS_DEBUG)	Set_tests.cpp -o  $(SET)
fclean:
	rm -f a.out $(RD_TREE)