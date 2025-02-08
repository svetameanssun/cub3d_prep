# ══ Names ═══════════════════════════════════════════════════════════════════ #
#    -----                                                                     #

NAME 				= minigame

# ══ Colors ══════════════════════════════════════════════════════════════════ #
#    ------                                                                    #

DEL_LINE 			= \033[2K
ITALIC 				= \033[3m
BOLD 				= \033[1m
DEF_COLOR 			= \033[0;39m
GRAY 				= \033[0;90m
RED 				= \033[0;91m
GREEN 				= \033[0;92m
YELLOW 				= \033[0;93m
BLUE 				= \033[0;94m
MAGENTA 			= \033[0;95m
CYAN 				= \033[0;96m
WHITE 				= \033[0;97m
BLACK 				= \033[0;99m
ORANGE 				= \033[38;5;209m
BROWN 				= \033[38;2;184;143;29m
DARK_GRAY 			= \033[38;5;234m
MID_GRAY 			= \033[38;5;245m
DARK_GREEN 			= \033[38;2;75;179;82m
DARK_YELLOW 		= \033[38;5;143m

# ══ Compilation══════════════════════════════════════════════════════════════ #
#    -----------                                                               #

CC 					= gcc
AR 					= ar rcs
RM 					= rm -f
MK 					= make -C
MKD					= mkdir -p
MCL 				= make clean -C
MFCL 				= make fclean -C
MK_					= && make

# ══ Directories ═════════════════════════════════════════════════════════════ #
#    -----------                                                               #

INCLUDE_DIR			= ./include
SRC_DIR				= ./src
MLX42_LIB			= ./MLX42/lib
MLX42_INCLUDE		= ./MLX42/include/MLX42

# ══ Library Archives ════════════════════════════════════════════════════════ #
#    ----------------                                                          #

LIBMLX42_A			= ${MLX42_LIB}/libmlx42.a

# ══ Flags ═══════════════════════════════════════════════════════════════════ #
#    -----                                                                     #

CFLAGS 				= -Wall -Werror -Wextra
IFLAGS				= -I${INCLUDE_DIR} -I${MLX42_INCLUDE}
LFLAGS				= -L$(MLX42_LIB) -lmlx42 -lglfw -ldl -lm -lpthread

# ══ Sources ═════════════════════════════════════════════════════════════════ #
#    -------                                                                   #

SRC					= ${SRC_DIR}/minigame.c

# ══ Object ═════════════════════════════════════════════════════════════════ #
#    -------                                                                   #

OBJ					= $(patsubst ${SRC_DIR}/%.c, %.o, ${SRC})

# ═══ Rules ══════════════════════════════════════════════════════════════════ #
#     -----                                                                    #

all: ${NAME}

${NAME}: ${LIBMLX42_A} ${OBJ} 
	@echo "$(YELLOW)Compiling ...$(DEF_COLOR)"
	@${CC} ${CFLAGS} ${IFLAGS} -o ${NAME} ${OBJ} ${LFLAGS}
	@echo "$(GREEN) $(NAME) all created ✓$(DEF_COLOR)"

%.o: ${SRC_DIR}/%.c
	@${MKD} $(dir $@)
	@$(CC) ${CFLAGS} ${IFLAGS} -c $< -o $@

clean:
	@echo "$(YELLOW)Removing object files!$(DEF_COLOR)"
	@find -name "*.o" -type f -delete
	@echo "$(RED)Object files removed! $(DEF_COLOR)"

fclean: clean
	@echo "$(YELLOW)Removing binaries!$(DEF_COLOR)"
	@${RM} ${NAME}
	@echo "$(RED)Binaries removed! $(DEF_COLOR)"

re: fclean all

.PHONY : all clean fclean re
