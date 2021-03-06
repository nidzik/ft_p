#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nidzik <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/11 10:34:54 by nidzik            #+#    #+#              #
#    Updated: 2018/04/01 22:40:42 by nidzik           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

SERVER = serveur
CLIENT = client
# LIBFT
LFTPATH = libft/
LFTIPATH = -I $(LFTPATH)
LFT = -L $(LFTPATH) -lft


OBJPATHSERVER = obj_serv
SRCPATHSERVER = serv_srcs

OBJPATHCLI = obj_cli
SRCPATHCLI = cli_srcs

INCLUDE = -I ./includes/


CC = clang


LIBS = $(LFT)
INCLUDES = $(INCLUDE) $(LFTIPATH) 


BASEFLAGS = -Wall -Wextra

CFLAGS = $(BASEFLAGS) -Werror -O2 -g

SSERV = ""
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	SSERV += -lcrypt
endif

LFTCALL = all
LFTRE = re

SRCFILESERVER  =	main.c \
			error.c \
			handle_cmds.c \
			utils.c \
			handle_get_put.c \
			handle_quit.c \
			connect.c \
			manage_pass.c \
			norme.c \
			more.c

SRCFILECLI  =	main.c \
				error.c \
				handle_get.c \
				handle_rest.c \
				login.c \
				norme.c

SRCSERVER = $(addprefix $(SRCPATHSERVER)/,$(SRCFILESERVER))
OBJSERVER = $(SRCSERVER:$(SRCPATHSERVER)/%.c=$(OBJPATHSERVER)/%.o)

SRCCLI = $(addprefix $(SRCPATHCLI)/,$(SRCFILECLI))
OBJCLI = $(SRCCLI:$(SRCPATHCLI)/%.c=$(OBJPATHCLI)/%.o)

RM = rm -rf

Y = \033[0;33m
R = \033[0;31m
G = \033[0;32m
E = \033[39m

all: l $(SERVER) $(CLIENT)

$(SERVER): $(OBJSERVER) 
	@echo "$(Y)[COMPILING SERVER] $(G) $(CC) -o $@ $(CFLAGS) objs.o $(LIBS) $(E)"
	@$(CC)  -o $@ $(CFLAGS) $(SSERV) $(OBJSERVER) $(INCLUDES) $(LIBS)
	@echo "$(Y)[COMPILING SERVER DONE]$(E)"

$(OBJSERVER): $(OBJPATHSERVER)/%.o : $(SRCPATHSERVER)/%.c
	@mkdir -p $(dir $@)
	$(CC) -o $@ $(CFLAGS) $(INCLUDES) -c $<

$(CLIENT): $(OBJCLI) 
	@echo "$(Y)[COMPILING CLIENT] $(G) $(CC) -o $@ $(CFLAGS) objs.o $(LIBS) $(E)"
	@$(CC)  -o $@ $(CFLAGS) $(OBJCLI) $(INCLUDES) $(LIBS)
	@echo "$(Y)[COMPILING CLIENT DONE]$(E)"

$(OBJCLI): $(OBJPATHCLI)/%.o : $(SRCPATHCLI)/%.c
	@mkdir -p $(dir $@)
	$(CC) -o $@ $(CFLAGS) $(INCLUDES) -c $<

clean:
	$(RM) $(OBJPATHSERVER)
	$(RM) $(OBJPATHCLI)

fclean: clean
	$(RM) $(SERVER)
	$(RM) $(CLIENT)

l:
	@echo "$(Y)[COMPILING LIBFT] $(G) make -C $(LFTPATH) $(LFTCALL) $(E)"
	@make -C $(LFTPATH) $(LFTCALL)
	@echo "$(Y)[COMPILING LIBFT DONE]$(E)"

re: fclean all
