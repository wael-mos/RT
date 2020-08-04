# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: evogel <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/07 16:47:44 by evogel            #+#    #+#              #
#    Updated: 2019/04/10 18:53:11 by evogel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

############
# COMPILER #
############

CC = gcc

CFLAGS = -Wall -Wextra -Werror

DEBUG1 = -fsanitize=address

#########
# FILES #
#########

FT_PRINTF_SRCS = ft_printf.c \
				 get_arg.c \
				 get_fmt.c \
				 get_fns.c \
				 set_ppw.c \
				 treat_chr.c \
				 treat_flt.c \
				 treat_int.c \
				 treat_str.c \
				 treat_uns.c \
				 color_manager.c

SRCS = ft_atoi.c \
	   ft_itoa.c \
	   ft_itoabase.c \
	   ft_flotoa.c \
	   ft_isupper.c \
	   ft_islower.c \
	   ft_toupper.c \
	   ft_tolower.c \
	   ft_isalpha.c \
	   ft_isdigit.c \
	   ft_isalnum.c \
	   ft_isascii.c \
	   ft_isprint.c \
	   ft_capitalize.c \
	   ft_putchar.c \
	   ft_putchar_fd.c \
	   ft_putendl.c \
	   ft_putendl_fd.c \
	   ft_putnbr.c \
	   ft_putnbr_fd.c \
	   ft_putstr.c \
	   ft_putstr_fd.c \
	   ft_puttab.c \
	   ft_strcat.c \
	   ft_strchr.c \
	   ft_strclr.c \
	   ft_strcmp.c \
	   ft_strcpy.c \
	   ft_strdel.c \
	   ft_strdup.c \
	   ft_strequ.c \
	   ft_striter.c \
	   ft_striteri.c \
	   ft_strjoin.c \
	   ft_strlcat.c \
	   ft_strlen.c \
	   ft_strmap.c \
	   ft_strmapi.c \
	   ft_strncat.c \
	   ft_strncmp.c \
	   ft_strncpy.c \
	   ft_strnequ.c \
	   ft_strnew.c \
	   ft_strnstr.c \
	   ft_strrchr.c \
	   ft_strsplit.c \
	   ft_strstr.c \
	   ft_strsub.c \
	   ft_strtrim.c \
	   ft_bzero.c \
	   ft_memalloc.c \
	   ft_memccpy.c \
	   ft_memchr.c \
	   ft_memcmp.c \
	   ft_memcpy.c \
	   ft_memdel.c \
	   ft_memmove.c \
	   ft_memset.c \
	   ft_setmalloc.c \
	   ft_tabdel.c \
	   ft_lstadd.c \
	   ft_lstdel.c \
	   ft_lstdelone.c \
	   ft_lstiter.c \
	   ft_lstlen.c \
	   ft_lstmap.c \
	   ft_lstnew.c \
	   get_next_line.c \
	   ft_abs.c \
	   ft_pow.c

OBJS = $(SRCS:.c=.o) $(FT_PRINTF_SRCS:.c=.o)

INCS = libft.h \
	   ft_printf.h \
	   get_next_line.h

###############
# DIRECTORIES #
###############

P_INCS = .

P_SRCS = srcs

P_OBJS = objs

D_OBJS = $(addprefix $(P_OBJS)/, $(OBJS))

D_INCS = $(addprefix $(P_INCS)/, $(INCS))

################
# COMPILE TEST #
################

COM_COLOR   = \033[0;34m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m

define run_and_test
printf "%b" "$(COM_COLOR)$(COM_STRING) $(OBJ_COLOR)$(@F)$(NO_COLOR)\r"; \
	$(1) 2> $@.log; \
	RESULT=$$?; \
	if [ $$RESULT -ne 0 ]; then \
		printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(ERROR_COLOR)$(ERROR_STRING)$(NO_COLOR)\n"   ; \
	elif [ -s $@.log ]; then \
		printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(WARN_COLOR)$(WARN_STRING)$(NO_COLOR)\n"   ; \
	else  \
		printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $(@F)" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"   ; \
	fi; \
	cat $@.log; \
	rm -f $@.log; \
	exit $$RESULT
endef

OK_STRING    = "[OK]"
ERROR_STRING = "[ERROR]"
WARN_STRING  = "[WARNING]"
COM_STRING   = "Compiling"

#########
# RULES #
#########

all: $(NAME)

$(NAME): $(P_OBJS) $(D_OBJS)
	@ar -rc $(NAME) $(D_OBJS)
	@ranlib $(NAME)

$(P_OBJS)/%.o: $(P_SRCS)/%.c
	@$(CC) $(CFLAGS) -o $@ -c $< -I $(P_INCS)

$(P_OBJS)/%.o: $(P_SRCS)/ft_printf/%.c
	@$(CC) $(CFLAGS) -o $@ -c $< -I $(P_INCS)

$(P_OBJS):
	@mkdir -p $(P_OBJS)

clean:
	@rm -rf $(D_OBJS) $(P_OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all
