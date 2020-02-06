# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/08 16:39:52 by gsmith            #+#    #+#              #
#    Updated: 2020/02/06 15:21:35 by gsmith           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = clang
CFLAGS = -Wall -Wextra -Werror
SRCS = ft_memset.c \
	   ft_bzero.c \
	   ft_memcpy.c \
	   ft_memccpy.c \
	   ft_memmove.c \
	   ft_memchr.c \
	   ft_memcmp.c \
	   ft_strlen.c \
	   ft_strdup.c \
	   ft_strcpy.c \
	   ft_strncpy.c \
	   ft_strcat.c \
	   ft_strncat.c \
	   ft_strlcat.c \
	   ft_strchr.c \
	   ft_strrchr.c \
	   ft_strstr.c \
	   ft_strnstr.c \
	   ft_strcmp.c \
	   ft_strncmp.c \
	   ft_atoi.c \
	   ft_isalpha.c \
	   ft_isdigit.c \
	   ft_isalnum.c \
	   ft_isascii.c \
	   ft_isprint.c \
	   ft_toupper.c \
	   ft_tolower.c \
	   ft_memalloc.c \
	   ft_memdel.c \
	   ft_strnew.c \
	   ft_strdel.c \
	   ft_strclr.c \
	   ft_striter.c \
	   ft_striteri.c \
	   ft_strmap.c \
	   ft_strmapi.c \
	   ft_strequ.c \
	   ft_strnequ.c \
	   ft_strsub.c \
	   ft_strjoin.c \
	   ft_strtrim.c \
	   ft_strsplit.c \
	   ft_itoa.c \
	   ft_putchar.c \
	   ft_putstr.c \
	   ft_putendl.c \
	   ft_putnbr.c \
	   ft_putchar_fd.c \
	   ft_putstr_fd.c \
	   ft_putendl_fd.c \
	   ft_putnbr_fd.c \
	   ft_lstnew.c \
	   ft_lstdelone.c \
	   ft_lstdel.c \
	   ft_lstadd.c \
	   ft_lstiter.c \
	   ft_lstmap.c \
	   ft_isspace.c \
	   ft_islower.c \
	   ft_isupper.c \
	   ft_strrev.c \
	   ft_lstaddend.c \
	   ft_pow.c \
	   ft_sqrt.c \
	   ft_fact.c \
	   ft_itoa_b.c \
	   ft_iswap.c \
	   ft_cswap.c \
	   ft_itowchar.c \
	   ft_perror.c \
	   ft_lsttail.c \
	   ft_lstlen.c \
	   ft_atol.c \
	   ft_strsplit_fun.c \
	   ft_atoi_base.c \
	   ft_ltoa.c
OBJS = $(SRCS:.c=.o)

BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m

S_N = [0;
S_B = [1;
S_D = [2;
S_I = [3;
S_L = [4;

NC = \033[0m

PREFIX = $(subst $(S_N),$(S_D),$(WHITE))[$(NAME)] - $(NC)

all:
	@make $(NAME)

$(NAME): $(OBJS)
	@printf "\r$(PREFIX)$(GREEN)Compiling Done.                         \n$(NC)"
	@printf "$(PREFIX)$(YELLOW)Regrouping .o files to $(NAME)...$(NC)"
	@ar rc $(NAME) $(OBJS)
	@printf "\r$(PREFIX)$(GREEN)$(NAME) created.                        \n$(NC)"
	@printf "$(PREFIX)$(YELLOW)Indexing $(NAME)...$(NC)"
	@ranlib $(NAME)
	@printf "\r$(PREFIX)$(GREEN)$(NAME) indexed.                        \n$(NC)"

%.o: %.c libft.h
	@printf "$(PREFIX)$(YELLOW)compiling $<...                    \r$(NC)"
	@$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@printf "$(PREFIX)$(RED)Cleaning .o files...\r$(NC)"
	@rm -f $(OBJS)
	@printf "$(PREFIX)$(PURPLE).o files cleaned.           \n$(NC)"

fclean: clean
	@printf "$(PREFIX)$(RED)Cleaning $(NAME) file...$(NC)\r"
	@rm -f $(NAME)
	@printf "$(PREFIX)$(PURPLE)$(NAME) cleaned.            \n$(NC)"

re: fclean all
.PHONY: all clean fclean re
