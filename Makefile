# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/15 07:37:02 by mdziadko          #+#    #+#              #
#    Updated: 2025/05/09 15:09:54 by mdziadko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# **************************************************************************** #
# 								   VARIABLES								   #
# **************************************************************************** #

NAME		= fdf
CC 			= cc
CFLAGS		= -Wall -Wextra -Werror -g3 #-fsanitize=address
AR			= ar rcs
RM			= rm -f

# Detect OS
UNAME := $(shell uname)

# Platform-specific MiniLibX path
ifeq ($(UNAME), Darwin)
	MLX_DIR		= minilibx-mms
	MLX_LIB		= $(MLX_DIR)/libmlx.dylib
	MLX_FLAGS	= -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit \
				-Wl,-rpath,$(CURDIR)
else
	MLX_DIR		= minilibx-linux
	MLX_LIB		= $(MLX_DIR)/libmlx.a
	MLX_FLAGS	= -L$(MLX_DIR) -lmlx -lX11 -lXext
endif

# Directories
LIBFT_DIR		= libft
GNL_DIR			= gnl
PRINTF_DIR		= printf
LIBFT_LIB		= $(LIBFT_DIR)/libft.a
PRINTF_LIB		= $(PRINTF_DIR)/libftprintf.a
OBJ_DIR			= obj

# Includes and Libraries
INCLUDES		= -I. -I$(LIBFT_DIR) -I$(GNL_DIR) -I$(PRINTF_DIR) -I$(MLX_DIR)
LIBS			= $(LIBFT_LIB) $(PRINTF_LIB) $(MLX_LIB)

# **************************************************************************** #
# 									FILES									   #
# **************************************************************************** #

SRCS		= main.c init.c map_parse.c parse_utils.c project.c rotation.c \
			draw.c colors.c render.c cleanup.c events.c events_key.c
OBJS		= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
HEADERS		= fdf.h

# **************************************************************************** #
# 									RULES									   #
# **************************************************************************** #

all: $(LIBFT_LIB) $(PRINTF_LIB) $(MLX_LIB) $(NAME) 

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

$(PRINTF_LIB):
	$(MAKE) -C $(PRINTF_DIR)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(MLX_FLAGS) -lm -o $(NAME)

$(OBJ_DIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(PRINTF_DIR)
	$(MAKE) clean -C $(MLX_DIR) || true

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) fclean -C $(PRINTF_DIR)
	$(MAKE) fclean -C $(MLX_DIR) || true

re: fclean all

.PHONY: all clean fclean re