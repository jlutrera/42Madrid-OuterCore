# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jutrera <jutrera@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/09 11:10:11 by jutrera-          #+#    #+#              #
#    Updated: 2025/09/03 13:21:51 by jutrera          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME		=	rt

# Paths
O_DIR		=	obj
I_DIR		=	include
S_DIR		=	srcs

# Source files
SRCS		=	srcs/callbacks_compose.c \
				srcs/callbacks_create.c \
				srcs/callbacks_menu.c \
				srcs/cameras.c \
				srcs/check_entries.c \
				srcs/cJSON.c \
				srcs/create_compose.c \
				srcs/create_file.c \
				srcs/create_others.c \
				srcs/create_scene.c \
				srcs/create_slice.c \
				srcs/create_solids.c \
				srcs/create_texture.c \
				srcs/create_window.c \
				srcs/fig_cone.c \
				srcs/fig_cylinder.c \
				srcs/fig_moebius.c \
				srcs/fig_paraboloid.c \
				srcs/fig_plane.c \
				srcs/fig_sphere.c \
				srcs/fig_torus.c \
				srcs/filters.c \
				srcs/free_memory.c \
				srcs/gizmo.c \
				srcs/initialize.c \
				srcs/lights_shadows.c \
				srcs/main.c \
				srcs/messages.c \
				srcs/parse_cameras.c \
				srcs/parse_file.c \
				srcs/parse_instances.c \
				srcs/parse_library.c \
				srcs/parse_lights.c \
				srcs/parse_objects.c \
				srcs/parse_options.c \
				srcs/parse_solids.c \
				srcs/parse_utils.c \
				srcs/process_load.c \
				srcs/process_save.c \
				srcs/rays.c \
				srcs/ref_ref.c \
				srcs/render_scene.c \
				srcs/slices.c \
				srcs/stb_impl.c \
				srcs/textures.c \
				srcs/transformations.c

# Compiler and flags
CC			=	gcc
RM 			=	rm -rf
CFLAGS		=	-Wall -Wextra -Werror -Wpedantic -g3 -Wshadow
ASANFLAG	=	-fsanitize=address -fno-omit-frame-pointer -g
OTHERFLAGS	= 	-lpng -lfontconfig -fopenmp -pthread -lm
GTKFLAG		= 	`pkg-config --cflags --libs gtk+-3.0`

#  Colors
RED 		= 	\033[0;31m
GREEN	 	= 	\033[0;32m
YELLOW 		= 	\033[0;33m
RESET 		= 	\033[0m

# Delete files
RM 			= 	rm -rf

# Object files
OBJS 		= 	$(patsubst $(S_DIR)/%.c, $(O_DIR)/%.o, $(SRCS))

# Targets
all			:	$(NAME)

# Compile object files
$(O_DIR)/%.o: 	$(S_DIR)/%.c
				@mkdir -p $(dir $@)
				@printf "Compiling $(YELLOW)$<$(RESET)\r"
				@$(CC)  $(OTHERFLAGS) $(ASANFLAG)  -I$(I_DIR) -c $< -o $@ $(GTKFLAG)
				@printf "                                                        \r"

# Link program
$(NAME)		: 	$(OBJS)
				@echo "Compiling... $(GREEN)OK!$(RESET)"
				@echo "Linking object files... \c"
				@$(CC) $(OBJS) $(CFLAGS) $(OTHERFLAGS) $(ASANFLAG) -o $(NAME) $(GTKFLAG)
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

# Phony targets
.PHONY		:	all clean fclean re

# Execute with Valgrind and suppressions for GTK and GLib
# G_SLICE=always-malloc : makes sure GLib uses malloc/free 
#						  instead of its own memory allocator
# G_DEBUG=gc-friendly   : tells GLib to release more memory 
#						  when programs exit
leaks		:	$(NAME)
				G_DEBUG=gc-friendly G_SLICE=always-malloc \
				valgrind \
				--leak-check=full \
				--show-leak-kinds=definite \
				--suppressions=/usr/share/glib-2.0/valgrind/glib.supp \
				--suppressions=/usr/share/gtk-3.0/valgrind/gtk.supp \
				--suppressions=./gtk_leaks/gtk-extra.supp \
				./$(NAME) 

