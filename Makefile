# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/23 06:27:55 by nihuynh           #+#    #+#              #
#    Updated: 2018/09/23 01:16:10 by nihuynh          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	fractol
RUNMODE		:=	dev
#RUNMODE		:=	release
PARAM		:=	julia
#PARAM		:=	mandelbrot
SRC			:=	main.c mlx.c julbrot.c keyboard.c mouse.c palette.c thread.c \
				hud.c
HEADERS		:= fractol.h
# directories :
SRCDIR  	:=	srcs
OBJDIR 		:=	objs
INCDIR  	:=	includes
# LIBFT
LIBFT_NAME	:=	libft.a
LIBFT_PATH	:=	../../libft_project/master/
LIBFT_INC	:=	includes
# MINILIBX
LMLX_NAME	:=	libmlx.a
LMLX_PATH	:=	minilibx/
LMLX_INC	:=
# **************************************************************************** #
# make specs :
MYCC		:=	clang
MYCC		+=	-Werror -Wall -Wextra
ifeq ($(RUNMODE),dev)
    MYCC	+=	-g -O0
	#MYCC	+=	-Wpedantic -ggdb -fsanitize=address
else
	MYCC	+=	-O3
endif

RM			:=	/bin/rm -f
# **************************************************************************** #
# Automatic variable :
OBJ			:=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))
HEAD		:=	$(addprefix $(INCDIR)/, $(HEADERS))
# Includes :
INCF_FDF	:=	$(INCDIR)
INCF_LIBFT	:=	$(LIBFT_PATH)$(LIBFT_INC)
INCF_LMLX	:=	$(LMLX_PATH)$(LMLX_INC)
# Lib links :
LINKF_LIBFT	:=	$(LIBFT_PATH)$(LIBFT_NAME)
LINKF_LMLX	:=	$(LMLX_PATH)$(LMLX_NAME)
# Framework :
FRAME_W		:=	-framework OpenGL -framework AppKit
LIB			:=	-L $(LIBFT_PATH) -lft -L $(LMLX_PATH) -lmlx
INC			:=	-I$(INCF_LIBFT) -I$(INCF_LMLX) -I$(INCDIR)
# **************************************************************************** #
OKLOGO	:=	\033[80G\033[32m[OK]\033[0m\n
# **************************************************************************** #
# Target rules :
all: $(NAME)
$(NAME): $(OBJ) $(LINKF_LIBFT) $(LINKF_LMLX) $(HEAD)
	@$(MYCC) -o $@ $(OBJ) $(INC) $(LIB) $(FRAME_W)
	@printf "\n\033[1;34m$(NAME)\033[25G\033[32mBuilt $@ $(OKLOGO)"
$(LINKF_LIBFT):
	@make -C $(LIBFT_PATH)/
$(LINKF_LMLX):
	@make -C $(LMLX_PATH)/

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEAD)
	@mkdir $(OBJDIR) 2> /dev/null || true
	@$(MYCC) $(INC) -pthread -o $@ -c $<
	@printf "\033[1;34m$(NAME)\033[25G\033[33mCompile $< $(OKLOGO)"
clean:
	@$(RM) $(OBJ)
	@rmdir $(OBJDIR) 2> /dev/null || true
	@printf "\033[1;34m$(NAME)\033[25G\033[31mCleaning objs $(OKLOGO)"
lclean:
	@make -C $(LIBFT_PATH)/ clean
	@make -C $(LMLX_PATH)/ clean
fclean: clean lclean
	@make -C $(LIBFT_PATH)/ fclean
	@$(RM) $(NAME)
	@printf "\033[1;34m$(NAME)\033[25G\033[31mCleaning $(NAME) $(OKLOGO)"
re: fclean all
run: clean $(NAME)
	@./$(NAME) $(PARAM)
git: fclean
	@git add -A
	@printf "\033[1;34m$(NAME)\033[25G\033[31mGit sync $(OKLOGO)"
	@git status
norme:
	@norminette -R CheckForbiddenSourceHeader srcs includes playground
	@printf "\033[1;34m$(NAME)\033[25G\033[31mNorminette $(OKLOGO)"
.PHONY: all, $(NAME), clean, fclean, re, run, git, norme