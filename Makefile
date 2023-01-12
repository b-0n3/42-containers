COMPILER = c++
DEBUG_RB_TREE= -DDEBUG_RED_BLACK_TREE
FLAGS_DEBUG = --std=c++98 -Wall -Wextra -Werror -g  -fsanitize=address $(DEBUG_RB_TREE)
FLAGS = --std=c++98 -Wall -Wextra -Werror 

VECTOR=vector
MAP=map
STACK=stack
SET=set
RD_TREE=rd_tree

all: $(VECTOR) $(STACK) $(MAP)

$(VECTOR):
	@$(COMPILER) $(FLAGS)	src/vector/Vector_tests.cpp -o $(VECTOR)

$(MAP):
	@$(COMPILER) $(FLAGS)	src/map/Map_tests.cpp -o $(MAP)

$(STACK):
	@$(COMPILER) $(FLAGS)	src/stack/Stack_tests.cpp -o $(STACK)
$(RD_TREE):
	@$(COMPILER) $(FLAGS)	src/red-black-tree/RedBlackTreeTests.cpp -o $(RD_TREE)
$(SET):
	@$(COMPILER) $(FLAGS)	src/set/Set_tests.cpp -o  $(SET)


re: fclean all

clean:
	echo "cleaning "

bonus: $(SET)

cleanStack:
	rm -rf $(STACK)
cleanVector:
	rm -rf $(VECTOR)

cleanMap:
	rm -rf $(MAP)
cleanSet:
	rm -rf $(SET)

fcleanBonus: cleanSet

fclean:	cleanMap  cleanStack cleanVector
