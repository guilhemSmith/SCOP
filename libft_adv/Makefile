# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/08 16:39:52 by gsmith            #+#    #+#              #
#    Updated: 2020/02/06 15:36:25 by gsmith           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft_adv.a
CC=clang
CFLAGS=-Wall -Wextra -Werror
GNL_DIR = get_next_line
SRCS = $(GNL_DIR)/get_next_line.c
OBJS = $(SRCS:.c=.o)

PRINTF_DIR=ft_printf/
PRINTF_LIB=ft_printf/libftprintf.a
LIBFT_DIR=libft/

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

.PHONY: all
all:
	@make -C $(PRINTF_DIR) all
	@make $(NAME)

$(NAME): $(OBJS)
	@printf "\r$(PREFIX)$(GREEN)Compiling Done.                           \n$(NC)"
	@cp $(PRINTF_LIB) $(NAME)
	@printf "$(PREFIX)$(YELLOW)Regrouping .o files to $(NAME)...$(NC)"
	@ar rsc $(NAME) $(OBJS)
	@printf "\r$(PREFIX)$(GREEN)$(NAME) created.                        \n$(NC)"
	@printf "$(PREFIX)$(YELLOW)Indexing $(NAME)...$(NC)"
	@ranlib $(NAME)
	@printf "\r$(PREFIX)$(GREEN)$(NAME) indexed.                        \n$(NC)"

$(GNL_DIR)/%.o: $(GNL_DIR)/%.c
	@printf "$(PREFIX)$(YELLOW)Compiling $<...                    \r$(NC)"
	@$(CC) $(CFLAGS) -I $(GNL_DIR) -I $(LIBFT_DIR) -o $@ -c $<

.PHONY: clean
clean:
	@make -C $(PRINTF_DIR) clean
	@printf "$(PREFIX)$(RED)Cleaning .o files...\r$(NC)"
	@rm -f $(OBJS)
	@printf "$(PREFIX)$(PURPLE).o files cleaned.           \n$(NC)"

.PHONY: fclean
fclean: clean
	@make -C $(PRINTF_DIR) fclean
	@printf "$(PREFIX)$(RED)Cleaning .o files...\r$(NC)"
	@rm -f $(OBJS)
	@printf "$(PREFIX)$(PURPLE).o files cleaned.           \n$(NC)"
	@printf "$(PREFIX)$(RED)Cleaning $(NAME) file...$(NC)\r"
	@rm -f $(NAME)
	@printf "$(PREFIX)$(PURPLE)$(NAME) cleaned.            \n$(NC)"

.PHONY: re
re:
	@make fclean
	@make all