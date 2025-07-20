# Colors
RST = "\033[0m"
G   = "\033[32m"

# Project
NAME := philo_bonus

# Compiler
CC := cc
CFLAGS := -Wall -Wextra -Werror -Iincludes
RM := rm -f

# Folders
SRCDIR := srcs
OBJDIR := objs

# Files
SRCS := $(wildcard $(SRCDIR)/*.c)
OBJS := $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))

# Quiet build
QUIET = $(if $(filter 0,$(VERBOSE)),@,)

# Default target
all: $(OBJDIR) $(NAME)

# Create binary
$(NAME): $(OBJS)
	@echo $(G) "Compiling $(NAME)..." $(RST)
	$(QUIET)$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Compile .c to .o
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(QUIET)$(CC) $(CFLAGS) -c $< -o $@

# Create object dir
$(OBJDIR):
	@mkdir -p $(OBJDIR)

# Cleaning
clean:
	$(QUIET)$(RM) $(OBJS)

fclean: clean
	$(QUIET)$(RM) $(NAME)
	rm -rf objs

re: fclean all

.PHONY: all clean fclean re
