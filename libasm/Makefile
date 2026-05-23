# ===========================
#        CONFIGURACIÓN
# ===========================

NAME        =	main
NAME_B		= 	main_bonus

CC			= 	gcc
CFLAGS		= 	-Wall -Wextra -Werror -Iinclude -Itests -fno-pie -no-pie -MMD -MP

SRC_DIR		=	srcs

MAND_SRCS	= 	$(wildcard tests/mandatory/*.c)
MAND_OBJS	= 	$(MAND_SRCS:.c=.o)
MAND_DEPS	= 	$(MAND_OBJS:.o=.d)
ASM_SRCS	= 	$(wildcard $(SRC_DIR)/mandatory/*.s)
LIBASM      = 	$(SRC_DIR)/libasm.a

BONUS_SRCS	= 	$(wildcard tests/bonus/*.c)
BONUS_OBJS	= 	$(BONUS_SRCS:.c=.o)
BONUS_DEPS	= 	$(BONUS_OBJS:.o=.d)
ASM_SRCS_B	= 	$(wildcard $(SRC_DIR)/bonus/*.s)
LIBASM_B	=	$(SRC_DIR)/libasm_bonus.a

# ===========================
#          COLORES
# ===========================

GREEN   	= 	\033[1;32m
YELLOW  	= 	\033[1;33m
BLUE    	= 	\033[1;34m
RED     	= 	\033[1;31m
RESET   	= 	\033[0m

# ===========================
#          REGLAS
# ===========================

all			: 	$(LIBASM) $(NAME)

bonus		:	$(LIBASM_BONUS) $(NAME_B)

# --- Librería ASM ---
$(LIBASM)	:	$(ASM_SRCS)
				@echo "$(BLUE)[LIBASM]$(RESET) Compilando mandatory..."
				@$(MAKE) --no-print-directory -C $(SRC_DIR)
			
$(LIBASM_B)	:	$(ASM_SRCS_B)
				@echo "$(BLUE)[LIBASM]$(RESET) Compilando bonus..."
				@$(MAKE) bonus --no-print-directory -C $(SRC_DIR)
# --- Compilación de tests --- 
%.o			: 	%.c 
				@echo "$(BLUE)[CC]$(RESET) Compilando $<" 
				@$(CC) $(CFLAGS) -c $< -o $@

# --- Enlazado final ---
$(NAME)		: 	$(MAND_OBJS) $(LIBASM)
				@echo "$(GREEN)[OK]$(RESET) Enlazando main con libasm.a"
				@$(CC) $(CFLAGS) $(MAND_OBJS) -L$(SRC_DIR) -lasm -o $(NAME)
				@echo "$(GREEN)[DONE]$(RESET) Ejecutable creado: ./main"

$(NAME_B)	: 	$(BONUS_OBJS) $(LIBASM_B)
				@echo "$(GREEN)[OK]$(RESET) Enlazando main_bonus con libasm_bonus.a"
				@$(CC) $(CFLAGS) $(BONUS_OBJS) -L$(SRC_DIR) -lasm_bonus -o $(NAME_B)
				@echo "$(GREEN)[DONE]$(RESET) Ejecutable creado: ./main_bonus"

clean		:
				@$(MAKE) clean --no-print-directory -C $(SRC_DIR)
				@rm -f $(MAND_OBJS) $(BONUS_OBJS) $(MAND_DEPS) $(BONUS_DEPS)
				@echo "$(YELLOW)[CLEAN]$(RESET) Objetos eliminados"

fclean		: 	clean
				@$(MAKE) fclean --no-print-directory -C $(SRC_DIR)
				@rm -f $(NAME) $(NAME_B)
				@echo "$(RED)[FCLEAN]$(RESET) Ejecutables eliminados"

re			: 	fclean all

rebonus		:	fclean bonus

# ===========================
#        DEPENDENCIAS
# ===========================

-include $(MAND_DEPS) $(BONUS_DEPS)

# ===========================
#          PHONY
# ===========================

.PHONY		: 	all clean fclean re bonus rebonus
