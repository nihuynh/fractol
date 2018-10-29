# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/23 06:27:55 by nihuynh           #+#    #+#              #
#    Updated: 2018/10/09 14:42:49 by nihuynh          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	fractol
#RUNMODE		:=	dev
RUNMODE		:=	release
APP_NAME	:=	Fractal_Explorer
PARAM		:=	mandelbrot
SRC			:=	main.c render.c julbrot.c keyboard.c mouse.c palette.c thread.c\
				hud.c init.c
HEADERS		:= fractol.h
# directories :
SRCDIR  	:=	srcs
OBJDIR 		:=	objs
INCDIR  	:=	includes
# LIBFT
LIBFT_NAME	:=	libft.a
LIBFT_PATH	:=	../lib/libft/
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
    MYCC	+=	-g3 -O0
	#MYCC	+=	-Wpedantic -ggdb -fsanitize=address
else
	MYCC	+= -Ofast
endif
RM			:=	/bin/rm -f
FMKDIR		:= 2> /dev/null || true
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
.POSIX:
all: $(NAME)
$(NAME): $(OBJ) $(LINKF_LIBFT) $(LINKF_LMLX) $(HEAD)
	@$(MYCC) -o $@ $(OBJ) $(INC) $(LIB) $(FRAME_W)
	@printf "\n\033[1;34m$(NAME)\033[25G\033[32mBuilt $@ complete $(OKLOGO)"
$(LINKF_LIBFT):
	@make -C $(LIBFT_PATH)/
$(LINKF_LMLX):
	@make -C $(LMLX_PATH)/

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEAD)
	@mkdir $(OBJDIR) $(FMKDIR)
	@$(MYCC) $(INC) -pthread -o $@ -c $<
	@printf "\033[1;34m$(NAME)\033[25G\033[33mCompile $< $(OKLOGO)"
clean:
	@$(RM) $(OBJ)
	@rmdir $(OBJDIR) $(FMKDIR)
	@printf "\033[1;34m$(NAME)\033[25G\033[31mCleaning objs $(OKLOGO)"
lclean:
	@make -C $(LIBFT_PATH)/ clean
	@make -C $(LMLX_PATH)/ clean
aclean:
	@rm -rf "./build/$(APP_NAME).app/"
	@printf "\033[1;34m$(NAME)\033[25G\033[31mCleaning $(APP_NAME).app $(OKLOGO)"
built: $(NAME)
	@mkdir -p "./build/$(APP_NAME).app"/Contents/{MacOS,Resources} $(FMKDIR)
	@cp ./built_srcs/Info.plist "./build/$(APP_NAME).app/Contents/"
	@cp ./built_srcs/fe_icon.icns "./build/$(APP_NAME).app/Contents/Resources"
	@cp ./$(NAME) "./build/$(APP_NAME).app/Contents/MacOS/binary"
	@printf "\033[1;34m$(NAME)\033[25G\033[32mBuilt $(APP_NAME).app $(OKLOGO)"
fclean: clean lclean aclean
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
	@norminette -R CheckForbiddenSourceHeader srcs includes $(LIBFT_PATH)
	@printf "\033[1;34m$(NAME)\033[25G\033[31mNorminette $(OKLOGO)"
.PHONY: all, $(NAME), $(APP_NAME), clean, fclean, re, run, git, norme, aclean, built