# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/09 11:10:11 by jutrera-          #+#    #+#              #
#    Updated: 2026/01/21 11:09:52 by jutrera-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME		=	rt

# Paths
O_DIR		=	obj
I_DIR		=	include
S_DIR		=	srcs

# Source files
SRCS		=	$(wildcard $(S_DIR)/*.c)

# Object + dependency files
OBJS 		= 	$(patsubst $(S_DIR)/%.c, $(O_DIR)/%.o, $(SRCS))
DEPS 		= 	$(OBJS:.o=.d)

# Compiler and flags
CC			=	gcc
RM 			=	rm -rf
CFLAGS		=	-Wall -Wextra -Werror -Wpedantic -g3 -Wshadow -MMD -MP
OTHERFLAGS	= 	-lpng -lfontconfig -fopenmp -pthread -lm
GTKFLAG		= 	`pkg-config --cflags --libs gtk+-3.0`

#  Colors
RED 		= 	\033[0;31m
GREEN	 	= 	\033[0;32m
YELLOW 		= 	\033[0;33m
RESET 		= 	\033[0m

# Targets
all			:	$(NAME)

# Compile object files
$(O_DIR)/%.o: 	$(S_DIR)/%.c
				@mkdir -p $(dir $@)
				@printf "Compiling $(YELLOW)$<$(RESET)\r"
				@$(CC)  $(OTHERFLAGS) -I$(I_DIR) -c $< -o $@ $(GTKFLAG)
				@printf "                                                        \r"

# Link program
$(NAME)		: 	$(OBJS)
				@echo "Compiling... $(GREEN)OK!$(RESET)"
				@echo "Linking object files... \c"
				@$(CC) $(OBJS) $(CFLAGS) $(OTHERFLAGS) -o $(NAME) $(GTKFLAG)
				@echo "$(GREEN)OK!$(RESET)"
				@echo "Program $(YELLOW)rt$(GREEN) created successfully !\n$(RESET)"

# Clean object files
clean		:
				@echo "$(RED)Deleting object files... $(RESET)\c"
				@$(RM) $(O_DIR)
				@echo "$(GREEN)OK!$(RESET)"

# Clean everything and recompile
fclean		: 	clean
				@echo "$(RED)Deleting object and binary files... $(RESET)\c"
				@$(RM) $(NAME)
				@echo "$(GREEN)OK!$(RESET)"

# Recompile everything
re			: 	fclean all

# Include dependency files
-include $(DEPS)

# Phony targets
.PHONY		:	all clean fclean re