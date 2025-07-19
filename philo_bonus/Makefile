# Project: so_long
MAKEFLAGS += --no-print-directory
NAME := philo_bonus

# Compiler and flags
CC := cc
CFLAGS := -Wall -Wextra -Werror -O3
RM := rm -f

# Function to set show commands or not
QUIET = $(if $(filter 0,$(VERBOSE)),@,)

# Files
SRCS := clean_bonus.c error_bonus.c init_bonus.c parsing_bonus.c philo_bonus.c safe_functions_bonus.c utils_bonus.c

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