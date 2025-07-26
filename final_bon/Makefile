# Colors
RST = "\033[0m"
G   = "\033[32m"

# Project
NAME := philo_bonus

# Compiler
CC := cc
CFLAGS := -Iincludes #-Wall -Wextra -Werror
RM := rm -f

# Folders
SRCDIR := srcs
OBJDIR := objs

# Files — ленивое вычисление
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))

# Quiet build
QUIET = $(if $(filter 0,$(VERBOSE)),@,)

# Default target
all: prepare $(OBJDIR) $(NAME)

# Копировать .c и .h файлы
prepare:
	@mkdir -p $(SRCDIR) $(OBJDIR) includes
	@cp raw_src/*.c $(SRCDIR)/ 2>/dev/null || true
	@cp raw_includes/*.h includes/ 2>/dev/null || true

# Create binary
$(NAME): $(OBJS)
	@echo $(G) "Compiling $(NAME)..." $(RST)
	@echo "SRC FILES:" $(SRCS)
	@echo "OBJ FILES:" $(OBJS)
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
	rm -rf objs includes srcs

re: fclean all

val:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./philo_bonus 4 800 200 200

cp:
	mkdir -p srcs includes
	@echo "Copying source files..."
	cp *.c srcs/
	cp *.h includes/

vr:
	make cp
	make all
	clear
	make val

nr:
	make cp
	make all
	clear
	./philo_bonus 4 800 200 200

nrl:
	make cp
	make all
	clear
	./philo_bonus 4 800 200 200 5

rmf:
	rm -rf srcs includes objs

.PHONY: all clean fclean re
