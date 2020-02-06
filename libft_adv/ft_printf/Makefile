# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/08 16:39:52 by gsmith            #+#    #+#              #
#    Updated: 2020/02/06 15:46:00 by gsmith           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = clang
CFLAGS = -Wall -Wextra -Werror
SRCS = ft_printf.c \
	   ft_error.c \
	   ft_format.c \
	   convert_c.c \
	   convert_s.c \
	   convert_percent.c \
	   convert_p.c \
	   read_digits1.c \
	   read_digits2.c \
	   read_udigits1.c \
	   read_udigits2.c \
	   convert_d.c \
	   convert_u.c \
	   convert_o.c \
	   convert_x.c
OBJS = $(SRCS:.c=.o)

LIBFT_DIR = ../libft/
LIBFT_LIB = ../libft/libft.a

DPDS = $(SRCS:.c=.d)

# Color and output macros

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
	@make $(LIBFT_LIB)
	@make $(NAME)

$(NAME): $(OBJS)
	@printf "\r$(PREFIX)$(GREEN)Compiling Done.                         \n$(NC)"
	cp $(LIBFT_LIB) $(NAME)
	@printf "$(PREFIX)$(YELLOW)Compiling $(subst $(S_N),$(S_B),$(YELLOW))$(NAME)$(YELLOW) binary...$(NC)\r"
	ar rsc $(NAME) $(OBJS)
	@printf "\r$(PREFIX)$(GREEN)$(NAME) created.                        \n$(NC)"
	@printf "$(PREFIX)$(YELLOW)Indexing $(NAME)...$(NC)"
	ranlib $(NAME)
	@printf "\r$(PREFIX)$(GREEN)$(NAME) indexed.                        \n$(NC)"

%.o: %.c
	@printf "$(PREFIX)$(YELLOW)Compiling $@...                          $(NC)\r"
	$(CC) $(CFLAGS) -I $(LIBFT_DIR) -o $@ -c $<

%.d: %.c
	@printf "$(PREFIX)$(YELLOW)Writing dependency $@...$(NC)\r"
	$(CC) $(CFLAGS) -I $(LIBFT_DIR) -MM $^ > $@
	@printf "$(PREFIX)$(CYAN)Dependency $@ updated.  \n$(NC)"

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR) all

clean: dclean
	@make -C $(LIBFT_DIR) clean
	@printf "$(PREFIX)$(RED)Cleaning object files...$(NC)\r"
	rm -f $(OBJS)
	@printf "$(PREFIX)$(PURPLE)Object files cleaned.   \n$(NC)"

fclean: dclean
	@make -C $(LIBFT_DIR) fclean
	@printf "$(PREFIX)$(RED)Cleaning object files...$(NC)\r"
	rm -f $(OBJS)
	@printf "$(PREFIX)$(PURPLE)Object files cleaned.   \n$(NC)"
	@printf "$(PREFIX)$(subst $(S_N),$(S_B),$(RED))Deleting $(NAME)$(RED) binary...$(NC)\r"
	rm -f $(NAME)
	@printf "$(PREFIX)$(PURPLE)Binary $(subst $(S_N),$(S_B),$(PURPLE))$(NAME)$(PURPLE) deleted.          \n$(NC)"

re:
	@make fclean
	@make all

dclean:
	@printf "$(PREFIX)$(RED)Cleaning dependencies files...$(NC)\r"
	rm -f $(DPDS)
	@printf "$(PREFIX)$(PURPLE)Dependencies files cleaned.   \n$(NC)"

-include $(DPDS)

.PHONY: all clean fclean re dclean
