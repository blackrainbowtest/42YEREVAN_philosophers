# Colors
RST = "\033[0m"
G   = "\033[32m"

# Project
NAME := philo

# Compiler
CC := cc
# CFLAGS := -Wall -Wextra -Werror
RM := rm -f

# Source files (указаны явно)
SRC_FILES := init.c monitor.c philo.c simulate.c utils_exit.c utils_text.c utils_time.c
OBJS := $(SRC_FILES:.c=.o)

# Quiet build
QUIET = $(if $(filter 0,$(VERBOSE)),@,)

# Default target
all: $(NAME)

# Create binary
$(NAME): $(OBJS)
	@echo $(G) "Compiling $(NAME)..." $(RST)
	$(QUIET)$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Compile .c to .o
%.o: %.c
	$(QUIET)$(CC) $(CFLAGS) -c $< -o $@

# Cleaning
clean:
	$(QUIET)$(RM) $(OBJS)

fclean: clean
	$(QUIET)$(RM) $(NAME)

re: fclean all

val:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) 4 200 200 200

vr:
	$(MAKE) re
	clear
	$(MAKE) val

nr:
	$(MAKE) re
	clear
	./$(NAME) 4 800 200 200

nrl:
	$(MAKE) re
	clear
	./$(NAME) 105 800 200 200

.PHONY: all clean fclean re val vr nr nrl
