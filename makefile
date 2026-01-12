CC = gcc
CFLAG = -g -Wall -Wextra -Werror -Iinclude -Iprintf -Ilibft
RM = rm -rf

SRC = src/list_ls/listUtils.c \
	src/dirStream/dirStream.c\
	src/utils/utils.c\
	src/main.c

OBJS = $(SRC:.c=.o)
NAME = ft_ls
HEADER = include/ls_list.h \
include/dirStream.h \
include/ft_ls.h \
include/utils.h

LIBFT_A = libft/libft.a
PRINTF_A = printf/libftprintf.a

all : $(NAME)

$(NAME): $(OBJS) $(LIBFT_A) $(PRINTF_A)
	@$(CC) -o $@ $^

$(LIBFT_A):
	@make -C libft/ 

$(PRINTF_A):
	@make -C printf/

%.o : %.c $(HEADER)
	@$(CC) $(CFLAG) -c $< -o $@

clean :
	@make clean -C libft/
	@make clean -C printf/
	@$(RM) $(OBJS)

fclean :
	@make fclean -C libft/
	@make fclean -C printf/
	@$(RM) $(OBJS) $(NAME)

re : 
	@make fclean
	@make all

.PHONY: all clean fclean re