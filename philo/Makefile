# Project: so_long
MAKEFLAGS += --no-print-directory
NAME := philo

# Compiler and flags
CC := cc
CFLAGS := -Wall -Wextra -Werror -O3
RM := rm -f

# Function to set show commands or not
QUIET = $(if $(filter 0,$(VERBOSE)),@,)

# Files
SRCS := dinner.c getters_setters.c init.c philo.c monitor.c parsing.c safe_functions.c synchro_utils.c utils.c write.c

OBJS := $(SRCS:.c=.o)

all: $(NAME) clean

# Link the object files to create the executable
$(NAME): $(OBJS)
	$(QUIET)$(CC) $(OBJS) -o $(NAME)

# Object file generation rules
%.o: %.c
	$(QUIET)$(CC) $(CFLAGS) -c $< -o $@

# Clean rules
clean:
	$(QUIET)$(RM) $(OBJS)

fclean: clean
	$(QUIET)$(RM) $(NAME)

# Rebuild rules
re: fclean all

t:
	./$(NAME) $(ARGS)

.PHONY: all clean fclean re