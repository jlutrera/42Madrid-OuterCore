# ===========================
#        CONFIGURACIÓN
# ===========================

NAME			= libasm.a
BONUS_NAME		= libasm_bonus.a

MANDATORY_SRCS	= $(wildcard mandatory/*.s)
BONUS_SRCS		= $(wildcard bonus/*.s)

MANDATORY_OBJS 	= $(MANDATORY_SRCS:.s=.o)
BONUS_OBJS     	= $(BONUS_SRCS:.s=.o)

NASM			= nasm -f elf64 -g -F dwarf

# ===========================
#          COLORES
# ===========================

GREEN			= \033[1;32m
YELLOW			= \033[1;33m
BLUE			= \033[1;34m
RED				= \033[1;31m
RESET			= \033[0m

# ===========================
#          REGLAS
# ===========================

all				: $(NAME)
bonus			: $(BONUS_NAME)

# Compilación genérica de .s → .o
%.o				: %.s
				  @echo "$(BLUE)[ASM]$(RESET) Compilando $<"
				  @$(NASM) $< -o $@

$(NAME)			: $(MANDATORY_OBJS)
				  @ar rcs $(NAME) $(MANDATORY_OBJS)
				  @echo "$(GREEN)[OK]$(RESET) Librería mandatory creada: $(NAME)"
$(BONUS_NAME)	: $(BONUS_OBJS)
				  @ar rcs $(BONUS_NAME) $(BONUS_OBJS)
				  @echo "$(GREEN)[OK]$(RESET) Librería bonus creada: $(BONUS_NAME)"

clean			:
				  @rm -f $(MANDATORY_OBJS) $(BONUS_OBJS)
				  @echo "$(YELLOW)[CLEAN]$(RESET) Objetos eliminados"
 
fclean			: clean
				  @rm -f $(NAME) $(BONUS_NAME)
				  @echo "$(RED)[FCLEAN]$(RESET) Librerías eliminadas"

re				: fclean all

# ===========================
#          PHONY
# ===========================

.PHONY			: all clean fclean re bonus
