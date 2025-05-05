# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/14 16:28:37 by mdziadko          #+#    #+#              #
#    Updated: 2025/04/23 22:08:06 by mdziadko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# 								   VARIABLES								   #
# **************************************************************************** #

NAME		= libftprintf.a
CC 			= cc
CFLAGS		= -Wall -Wextra -Werror
AR			= ar rcs
RM			= rm -f

# Directories
LIBFT_DIR	= ../libft
LIBFT_LIB	= $(LIBFT_DIR)/libft.a

# Includes
INCLUDES	= -I. -I$(LIBFT_DIR)

# **************************************************************************** #
# 									FILES									   #
# **************************************************************************** #

SRCS		= ft_printf.c num_func.c str_func.c
OBJS		= $(SRCS:.c=.o)

# **************************************************************************** #
# 									RULES									   #
# **************************************************************************** #

all: $(LIBFT_LIB) $(NAME)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS) 

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re