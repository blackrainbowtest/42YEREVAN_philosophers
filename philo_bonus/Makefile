# Colors
RST = "\033[0m"
G   = "\033[32m"

# Project
NAME := philo_bonus

# Compiler
CC := cc
CFLAGS := -Wall -Wextra -Werror
RM := rm -f

# Source files (указаны явно)
SRC_FILES := philo_bonus.c \
			 init_bonus.c \
			 utils_time_bonus.c utils_text_bonus.c start_bonus.c philo_life_bonus.c
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

.PHONY: all clean fclean re
