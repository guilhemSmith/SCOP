# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/08 13:43:45 by gsmith            #+#    #+#              #
#    Updated: 2020/02/19 18:16:29 by gsmith           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


ifndef VERBOSE
.SILENT: 
endif

# OS
UNAME = $(shell uname)

# Compiling macros

NAME = scop

CC = clang
DEBUG = -g3
CFLAGS = -Wall -Werror -Wextra

## directories and files

LIBFT = libft_adv.a
DIR_LIBFT = libft_adv/
FLAG_LIBFT = -L./$(DIR_LIBFT) -lft_adv

GLFW = glfw
GLEW = glew
EXTERN = $(GLFW) $(GLEW)
DIR_EXTERN = $(HOME)/.brew/include
FLAG_EXTERN = -L $(HOME)/.brew/lib -lglfw -lglew -framework OpenGl

DIR_SRC = src
DIR_BUILD = build
DIR_DEP = depend
DIR_INC = include

FILES_SRC = \
	input.c \
	matrix.c \
	loader.c \
	renderer.c \
	scop.c \
	shader.c \
	utils_files.c \
	utils_loader.c \
	utils_loader_gl.c \
	utils_matrix.c \
	utils_scop.c \
	texture.c \
	vector.c
FILES_BUILD = $(FILES_SRC:.c=.o)
FILES_DEP = $(FILES_SRC:.c=.d)

SRC = $(addprefix $(DIR_SRC)/, $(FILES_SRC))
BUILD = $(addprefix $(DIR_BUILD)/, $(FILES_BUILD))
DEP = $(addprefix $(DIR_DEP)/, $(FILES_DEP))
INC = -I $(DIR_INC) -I $(DIR_LIBFT) -I $(HOME)/.brew/include

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

# Build all and rebuild

.PHONY: all
all:
	@Make -C libft_adv all
	@Make $(EXTERN)
	@Make $(NAME)

.PHONY: re
re:
	@Make fclean
	@Make all

# Binary and object files building

$(NAME): $(BUILD) $(DIR_LIBFT)$(LIBFT)
ifndef VERBOSE
	printf "$(PREFIX)$(YELLOW)Compiling $(subst $(S_N),$(S_B),$(YELLOW))$(NAME)$(YELLOW) binary...$(NC)\r"
endif
	$(CC) $(CFLAGS) $(INC) $(FLAG_EXTERN) $(FLAG_LIBFT) -o $@ $(BUILD)
ifndef VERBOSE
	printf "$(PREFIX)$(BLUE)Binary $(subst $(S_N),$(S_B),$(BLUE))$(NAME)$(BLUE) ready.      \n$(NC)"
endif

$(DIR_BUILD)/%.o: $(DIR_SRC)/%.c
ifndef VERBOSE
	printf "$(PREFIX)$(YELLOW)Compiling $@...$(NC)\r"
endif
	mkdir -p $(DIR_BUILD)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<
ifndef VERBOSE
	printf "$(PREFIX)$(BLUE)File $@ compiled.\n$(NC)"
endif

# Depend files building

$(DIR_DEP)/%.d: $(DIR_SRC)/%.c
ifndef VERBOSE
	printf "$(PREFIX)$(YELLOW)Writing dependency $@...$(NC)\r"
endif
	mkdir -p $(DIR_DEP)
	$(CC) $(CFLAGS) -D DEP=1 $(INC) -MT $(@:$(DIR_DEP)/%.d=$(DIR_BUILD)/%.o) -MM $< \
		| sed 's,\(.*\)\.o[ :]*,\1.o $@ : ,g' > $@
ifndef VERBOSE
	printf "$(PREFIX)$(CYAN)Dependency $@ updated.  \n$(NC)"
endif

# glfw and glew install and configuration

.PHONY: $(GLFW)
$(GLFW):
ifeq ($(UNAME), Darwin)
ifeq (, $(shell which brew))
	$(error "brew is missing in $(PATH).")
else
ifeq (,$(shell brew list | grep $(GLFW)))
	printf "$(PREFIX)$(subst $(S_N),$(S_B),$(YELLOW))$(GLFW)$(YELLOW) is missing, installing it from brew...$(NC)\r"
	brew install $(GLFW) >/dev/null 2>/dev/null
	printf "$(PREFIX)$(subst $(S_N),$(S_B),$(GREEN))$(GLFW)$(GREEN) installed.                              $(NC)\n"
else
endif
endif
endif

.PHONY: $(GLEW)
$(GLEW):
ifeq ($(UNAME), Darwin)
ifeq (, $(shell which brew))
	$(error "brew is missing in $(PATH).")
else
ifeq (,$(shell brew list | grep $(GLEW)))
	printf "$(PREFIX)$(subst $(S_N),$(S_B),$(YELLOW))$(GLEW)$(YELLOW) is missing, installing it from brew...$(NC)\r"
	brew install $(GLEW) >/dev/null 2>/dev/null
	printf "$(PREFIX)$(subst $(S_N),$(S_B),$(GREEN))$(GLEW)$(GREEN) installed.                              $(NC)\n"
else
endif
endif
endif

# Files cleaning

.PHONY: cleanobj
cleanobj:
ifndef VERBOSE
	printf "$(PREFIX)$(RED)Cleaning object files...$(NC)\r"
endif
	rm -f $(BUILD)
	rm -df $(DIR_BUILD) 2>/dev/null || True
ifndef VERBOSE
	printf "$(PREFIX)$(PURPLE)Object files cleaned.   \n$(NC)"
	printf "$(PREFIX)$(RED)Cleaning dependencies files...$(NC)\r"
endif
	rm -f $(DEP)
	rm -rf $(DIR_DEP) 2>/dev/null || True
ifndef VERBOSE
	printf "$(PREFIX)$(PURPLE)Dependencies files cleaned.   \n$(NC)"
endif

.PHONY: clean
clean: cleanobj
	@Make -C $(DIR_LIBFT) clean

.PHONY: fclean
fclean: cleanobj
ifndef VERBOSE
	printf "$(PREFIX)$(subst $(S_N),$(S_B),$(RED))Deleting $(NAME)$(RED) binary...$(NC)\r"
endif
	rm -f $(NAME)
ifndef VERBOSE
	printf "$(PREFIX)$(PURPLE)Binary $(subst $(S_N),$(S_B),$(PURPLE))$(NAME)$(PURPLE) deleted.          \n$(NC)"
endif
	@Make -C $(DIR_LIBFT) fclean

# check the norme

.PHONY: norme
norme:
	norminette src include  > .norm.tmp
	(grep "Error" -B 1 .norm.tmp && echo "$(subst $(S_N),$(S_B),$(RED))Norme error(s) found$(NC)\n") \
	|| echo "$(subst $(S_N),$(S_B),$(GREEN))No error found$(NC)\n"
	rm .norm.tmp

# include depend files

-include $(DEP)