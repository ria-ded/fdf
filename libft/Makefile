# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/15 20:58:49 by mdziadko          #+#    #+#              #
#    Updated: 2025/05/09 15:36:44 by mdziadko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# 								   VARIABLES								   #
# **************************************************************************** #

NAME		= libft.a
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
AR			= ar rcs
RM			= rm -f
OBJ_DIR		= obj

# **************************************************************************** #
# 									FILES									   #
# **************************************************************************** #

SRCS		= ft_isdigit.c ft_memset.c ft_strdup.c ft_strncmp.c ft_atoi.c \
			ft_isprint.c ft_putchar_fd.c ft_striteri.c ft_strnstr.c \
			ft_bzero.c ft_itoa.c ft_putendl_fd.c ft_strjoin.c ft_strrchr.c \
			ft_calloc.c ft_memchr.c ft_putnbr_fd.c ft_strlcat.c ft_strtrim.c \
			ft_isalnum.c ft_memcmp.c ft_putstr_fd.c ft_strlcpy.c ft_substr.c \
			ft_isalpha.c ft_memcpy.c ft_split.c ft_strlen.c ft_tolower.c \
			ft_isascii.c ft_memmove.c ft_strchr.c ft_strmapi.c ft_toupper.c \
			ft_isspace.c ft_lstnew.c ft_lstadd_front.c \
			ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
			ft_lstclear.c ft_lstiter.c ft_lstmap.c get_next_line.c
OBJS		= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# **************************************************************************** #
# 									RULES									   #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus