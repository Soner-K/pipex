NAME				=	pipex

LIBRARY_PATH		=	libft
LIBRARY				=	libft.a
LIBFT				=	$(addprefix $(LIBRARY_PATH)/,$(LIBRARY))

FILES				=	utils.c \
						path_finding.c \

MANDATORY			=	src/pipex.c \
MANDATORY_OBJ		=	$(MANDATORY:.c=.o)

BONUS				= 	src/pipex_bonus.c \
BONUS_OBJ			=	$(BONUS:.c=.o)

SRC_DIR				=	src
SRC					=	$(addprefix $(SRC_DIR)/,$(FILES))

OBJ_DIR				= 	obj
OBJ					=	$(addprefix $(OBJ_DIR)/,$(FILES:.c=.o))

CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror -g3 -I includes

all					:	$(NAME)

$(OBJ_DIR)			:
						@mkdir -p $@

$(NAME)				:	$(OBJ_DIR) $(OBJ) $(MANDATORY_OBJ)
						@echo "\n"
						@echo "$(LYELLOW)Compiling libft... $(COLOR_END) $(FACE_YAWNING)"
						@make -s -C $(LIBRARY_PATH)
						@echo "$(GREEN)libft compiled. $(COLOR_END) $(FACE_MELT)\n"
						@echo "$(LYELLOW)Compiling pipex... $(COLOR_END) $(FACE_SHAKING)"
						@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
						@echo "$(GREEN)pipex compiled $(COLOR_END) $(FACE_EXPLODING) $(HACKERMAN)"

# $(MANDATORY_OBJ)/%.o : $(MANDATORY_FILES)/%.c
# 					$(CC) $(CFLAGS) -c $< -o $@
# 					@printf "$(YELLOW)%s created $(COLOR_END)\n" $@

$(OBJ_DIR)/%.o		:	$(SRC_DIR)/%.c
						$(CC) $(CFLAGS) -c $< -o $@
						@printf "$(YELLOW)%s created $(COLOR_END)\n" $@

bonus				:	$(OBJ_DIR) $(OBJ) $(OBJ_BONUS)
						@echo "\n"
						@echo "$(LYELLOW)Compiling libft... $(COLOR_END) $(FACE_YAWNING)"
						@make -s -C $(LIBRARY_PATH)
						@echo "$(GREEN)libft compiled. $(COLOR_END) $(FACE_MELT)\n"
						@echo "$(LYELLOW)Compiling pipex bonus... $(COLOR_END) $(FACE_SHAKING)"
						@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
						@echo "$(GREEN)pipex bonus compiled $(COLOR_END) $(FACE_EXPLODING) $(HACKERMAN)"

clean				:
						@rm -rf $(OBJ_DIR)
						@make -s -C libft clean
						@echo "$(BLUE)Removing object files... $(COLOR_END)$(FACE_SHAKING)"
						@sleep 0.2
						@echo "$(LBLUE)Object files removed $(COLOR_END)$(BYE)"

fclean				:	clean
						@echo "$(YELLOW) *******************************$(COLOR_END)"
						@echo "$(BLUE)Removing pipex's executable $(COLOR_END) $(FACE_SHAKING)"
						@rm -f $(NAME)
						@make -s -C libft fclean
						@echo "$(LBLUE)Pipex's executable removed $(COLOR_END) $(BYE)"

re					:	fclean all

.PHONY				:	all clean fclean re bonus



HACKERMAN			=	🧑‍💻

BYE					=	🙋

FACE_ESCUZME		=	🤓

FACE_SHAKING		=	🫨

FACE_MELT			=	🫠

FACE_YAWNING		=	🥱

FACE_EXPLODING		=	🤯

LGREEN				=	\033[1;32m

GREEN				=	\033[32m

LBLUE				=	\033[1;34m

BLUE				=	\033[34m

RED					=	\033[31m

LYELLOW				=	\033[1;33m

YELLOW				=	\033[33m

COLOR_END			=	\033[0m






