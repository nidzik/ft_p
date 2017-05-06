#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nidzik <nidzik@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/11 10:46:15 by nidzik            #+#    #+#              #
#    Updated: 2015/05/09 17:51:43 by nidzik           ###   ########.fr        #
#                                                                              #
#******************************************************************************#


CC = gcc
NAME = libft
CFLAGS = -Wall -Wextra -Werror
SRCS = \
	ft_strlen.c ft_strcpy.c ft_strcat.c ft_strncpy.c ft_strncat.c \
		ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_toupper.c ft_tolower.c ft_strcmp.c ft_strncmp.c ft_atoi.c ft_strstr.c \
		ft_strnstr.c ft_memset.c ft_strchr.c ft_strrchr.c ft_memalloc.c \
		ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c \
		ft_memcmp.c ft_memdel.c ft_realloc.c ft_putchar.c ft_putstr.c \
		ft_putendl.c ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
		ft_putnbr_fd.c ft_strclr.c ft_striter.c ft_strequ.c ft_strnequ.c \
		ft_strjoin.c ft_strnew.c ft_lstnew.c ft_lstadd.c ft_strlcat.c \
		ft_strdel.c ft_strsplit.c ft_itoa.c ft_strmap.c ft_striteri.c ft_strsub.c \
		ft_strmapi.c ft_strtrim.c ft_strdup.c
OBJECTS = $(SRCS:%.c=%.o)

all : $(NAME)

$(NAME): $(OBJECTS)
	@ar rc $(NAME).a $(OBJECTS)
	@ranlib libft.a

$(OBJECTS): %.o : %.c
	$(CC) -o $@ $(CFLAGS) -c $<
clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf libft.a
	rm -rf $(NAME)

re: fclean all
