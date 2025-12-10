# Program name
NAME 		=	computor

# Project directories
SRCDIR 		=	./srcs
INCDIR 		=	./include
OBJDIR 		=	./obj

# Compiler and flags
CC 			=	gcc
CFLAGS 		=	-Wall -Wextra -Werror
LEAKS 		=	-fsanitize=address -g
DEPFLAGS 	=	-MMD -MP  # Flags to generate dependency files

# Source files
SRCS		=	./srcs/main.c \
				./srcs/maths.c \
				./srcs/reduce.c \
				./srcs/solve.c \
				./srcs/utils.c

# Object files
OBJS 		= 	$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

# Color codes for terminal output
RED 		= 	\033[0;31m
GREEN	 	= 	\033[0;32m
YELLOW 		= 	\033[0;33m
RESET 		= 	\033[0m

# Delete files
RM 			= 	rm -rf

# Default target
all			: 	$(NAME)

# Compile object files

$(OBJDIR)/%.o: 	$(SRCDIR)/%.c
				@mkdir -p $(dir $@)
				@printf "Compiling $(YELLOW)$<$(RESET)\r"
				@$(CC) $(CFLAGS) $(LEAKS) $(DEPFLAGS) -I$(INCDIR) -c $< -o $@
				@printf "                                                                         \r"

# Link program
$(NAME)		: 	$(OBJS)
				@echo "Linking object files... \c"
				@$(CC) $(OBJS) $(CFLAGS) $(LEAKS) -o $(NAME)
				@echo "$(YELLOW)$(NAME) $(GREEN) created successfully !$(RESET)"

# Clean object files
clean		:
				@echo "$(RED)Deleting object files...$(RESET)\c"
				@$(RM) $(OBJDIR)
				@echo "$(GREEN) all object files DELETED !$(RESET)"

# Clean everything and recompile
fclean		: 	clean
				@echo "$(RED)Deleting object and binary files...$(RESET)\c"
				@$(RM) $(NAME)
				@echo "$(GREEN)all files DELETED !$(RESET)"

# Recompile everything
re			: 	fclean all

# Include dependency files (if they exist)
-include $(DEPS)

# Phony targets
.PHONY		: 	all clean fclean re
