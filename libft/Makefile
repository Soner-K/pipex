SRC		=	$(wildcard src/*.c) 

HEADER	=	libft.h

OBJ		=	$(SRC:.c=.o)

NAME	=	libft.a

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

EXEC	=	exec

all		:	$(NAME)
			
%.o		:	%.c
			@$(CC) $(CFLAGS) -c $< -o $@

$(NAME)		:	$(OBJ)
			@ar -rc $(NAME) $(OBJ)

clean		:	
			@rm -f $(OBJ) a.out $(EXEC)

fclean		:	clean
			@rm -f $(NAME)

re		:	fclean all

$(EXEC)	:	$(OBJ)
			@$(CC) $(CFLAGS) $^ -o $@

run		:	$(EXEC)
			@./$(EXEC)

.PHONY		:	all clean fclean re exec run
