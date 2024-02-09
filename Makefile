CC					=	cc

CFLAGS				=	-Wall -Wextra -Werror -g3

LIBRARY_PATH		=	libft

LIBRARY				=	libft.a

LIBFT				=	$(addprefix $(LIBRARY_PATH)/,$(LIBRARY))

FILES				=	pipex.c \
						utils.c \
						find_path.c \
						
SRC_DIR				=	src

OBJ_DIR				= 	obj

OBJ					= $(addprefix $(OBJ_DIR)/,$(FILES:.c=.o))

SRC					=	$(addprefix $(SRC_DIR)/,$(FILES))

NAME				=	pipex


all					:	$(NAME)

e					:	
						@echo "$(OBJ)"
						@echo "$(SRC)"

$(OBJ_DIR)			:	
						mkdir -p $@

$(OBJ_DIR)/%.o		:	%.c
						$(CC) $(CFLAGS) -c $< -o $@
						@printf "$(YELLOW)%s created $(FACE_ZZZ)\n$(COLOR_END)" $@


$(NAME)				:	$(OBJ_DIR) $(OBJ)
						@echo "$(LYELLOW)Compiling libft... $(COLOR_END) $(FACE_YAWNING)"
						@make -s -C $(LIBRARY_PATH)
						@echo "$(GREEN)libft compiled. $(COLOR_END) $(FACE_MELT)"
						@echo "$(LYELLOW)Compiling pipex... $(COLOR_END) $(FACE_SHAKING)"
						@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
						@echo "$(GREEN)pipex compiled $(COLOR_END) $(FACE_EXPLODING) $(HACKERMAN)"

clean				:
						@rm -f $(OBJ)
						@make -s -C libft clean
						@echo "$(BLUE)Removing object files... $(COLOR_END)$(FACE_SHAKING)"
						@sleep 0.2
						@echo "$(LBLUE)Object files removed $(COLOR_END)$(MAN_BYE)"

fclean				:	clean
						@echo "$(YELLOW) *******************************$(COLOR_END)"
						@echo "$(BLUE)Removing pipex $(COLOR_END) $(FACE_SHAKING)"
						@rm -f $(NAME)
						@make -s -C libft fclean
						@echo "$(LBLUE)Pipex removed $(COLOR_END) $(MAN_BYE)"

re					:	fclean all

.PHONY				:	all clean fclean re



HACKERMAN			=	🧑‍💻

MAN_BYE				=	🙋‍♂️

FACE_ZZZ			=	🤓

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






