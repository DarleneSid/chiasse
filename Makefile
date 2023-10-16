NAME	=	cube3d

DIR_SRCS		=	srcs

DIR_OBJS		=	objs

SRCS_NAMES		=	main.c map.c

OBJS_NAMES		=	${SRCS_NAMES:.c=.o}

DEPS			=	${SRCS_NAMES:.c=.d}

SRCS			=	$(addprefix $(DIR_SRCS)/,$(SRCS_NAMES))

OBJS			=	$(addprefix $(DIR_OBJS)/,$(OBJS_NAMES))

INC				=	-Iincludes

LIB				=	-Llibft -lft -Lft_printf -lftprintf

LIBFT			=	libft.a

PRINTF			=	libftprintf.a

CC				=	cc

CDFLAGS 		=	-MMD -MP

MLX_FLAGS		=	-lm -lmlx -lXext -lX11

CFLAGS			=	-Wall -Werror -Wextra

all:	${NAME}

bonus:	${BONUS}

$(DIR_OBJS):
	mkdir -p $(DIR_OBJS)

$(OBJS) : $(DIR_OBJS)/%.o : $(DIR_SRCS)/%.c
	$(CC) -g3 $(CFLAGS) $(CDFLAGS) $(INC) -c $< -o $@ 

$(OBJS_B) : $(DIR_OBJS)/%.o : $(DIR_SRCS_B)/%.c
	$(CC) -g3 $(CFLAGS) $(CDFLAGS) $(INC) -c $< -o $@ 

$(NAME): $(DIR_OBJS) $(OBJS) 
	make -C libft
	make -C ft_printf
	make -C mlx
	$(CC) -g3 ${INC} $(OBJS) $(LIB)  mlx/libmlx.a mlx/libmlx_Linux.a -L. -lXext -L. -lX11 -o $(NAME)
	@echo "\033[31;5mcube3d\033[0m"


norm:
	norminette srcs/ bonus/ includes/

clean:
	make clean -C mlx
	make clean -C libft
	make clean -C ft_printf
	rm -rf ${DIR_OBJS}

fclean:	clean
	make fclean -C libft
	make fclean -C ft_printf
	rm -rf ${LIBFT}
	rm -rf ${NAME}
	rm -rf ${BONUS}

re:	fclean all

-include $(DEPS)

.PHONY:	all clean fclean re

