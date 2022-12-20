INC= ./src


all:
	make vector -C ./src/ft_containers_tests

fclean:
	 rm -rf ./src/ft_containers_tests/vector.out
