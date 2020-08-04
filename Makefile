# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: evogel <evogel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/07 16:47:44 by evogel            #+#    #+#              #
#    Updated: 2020/07/30 16:23:36 by achoquel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT

OS = $(shell uname)

#########
# FILES #
#########

SRCS = 		main.c 							\
		  		parsing.c 					\
		  		parsing1.c 					\
	   	 		parsing_light.c 					\
	   	 		parsing_obj.c 					\
	   	 		parse_perlin_water.c \
				parsing_tools.c \
	   	 		tools.c 			\
	   	 		tools_rot.c					\
	   	 		tools_exit.c 				\
		 	 	screenshot.c 				\
	   			opencl_init.c 			\
	   	 		opencl_run_kernel.c			\
				exporter_core.c \
				exporter_camera.c \
				exporter_lights.c \
				exporter_perlin.c \
				exporter_water.c \
				exporter_object.c \
				exporter_object2.c

OBJS = $(SRCS:.c=.o)

CL_SRCS = kernel.hl 						\
		  		tools.cl 						\
		  		effects.cl 					\
		  		rotate.cl 						\
		  		intersect.cl				  \
		  		render_scene.cl 			\
					noise.cl 						\
		  		quartic.cl 						\
		  		normal_perturb.cl

UI_SRCS = widget_init1.c 			\
					widget_init2.c 			\
					widget_init3.c 			\
					callback_init1.c    \
					callback_init2.c    \
					callback_sinewave.c \
					callback_perlin1.c	\
					callback_perlin2.c	\
					callback_perlin3.c	\
					callback_object1.c  \
					callback_object2.c  \
					callback_object3.c  \
					callback_object4.c  \
					callback_object5.c  \
					callback_object6.c  \
					callback_object7.c  \
					callback_object8.c  \
					callback_keyboard.c \
					callback_light1.c		\
					callback_light2.c		\
					callback_blocker.c \
					callback_unblocker.c \
					callback_blocker2.c \
					callback_unblocker2.c \
					callback_effect.c		\
					callback_effect2.c		\
					callback_camera1.c	\
					callback_camera2.c	\
					callback_addobj1.c	\
					callback_addobj2.c	\
					callback_addobj3.c	\
					callback_openscene.c \
					callback_fog.c 				\
					callback_deleteobj.c

UI_OBJS = $(UI_SRCS:.c=.o)

###############
# DIRECTORIES #
###############

INC = incs

P_SRCS = srcs

P_UI = ui

P_OBJS = objs

D_OBJS = $(addprefix $(P_OBJS)/, $(OBJS))

P_CL_SRCS = $(P_SRCS)/kernel

P_UI_SRCS = $(P_UI)/srcs

CL_FILES = $(addprefix $(P_CL_SRCS)/, $(CL_SRCS))

UI_FILES = $(addprefix $(P_UI_SRCS)/, $(UI_SRCS))

D_UI_OBJS = $(addprefix $(P_OBJS)/, $(UI_OBJS))

CL_KERNEL = $(addprefix $(P_CL_SRCS)/, kernel.cl)

#############
# LIBRARIES #
#############

LIBS = libft.a

D_LIBS = $(foreach LIB, $(LIBS), $(basename $(LIB))/$(LIB))

############
# COMPILER #
############

CC = gcc

CFLAGS = -g -Wall -Wextra -Werror -Wno-deprecated-declarations

ifeq ($(OS),Darwin)
else
	CFLAGS += -rdynamic
endif

GTK_IFLAGS = $(shell pkg-config --cflags gtk+-3.0)

GTK_LFLAGS = $(shell pkg-config --libs gtk+-3.0)

I_FLAGS = $(foreach LIB, $(LIBS),-I$(basename $(LIB))) -I$(INC)

L_FLAGS = $(foreach LIB, $(LIBS),-L$(basename $(LIB)) -l$(LIB:lib%.a=%)) -lm

ifeq ($(OS),Darwin)
	CL_LFLAG = -framework OpenCL
else
	CL_LFLAG = -lOpenCL
endif

XML_LFLAGS = -lxml2

XML_IFLAGS = -Ilibxml2/2.9.9_2/include/libxml2/

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

all: $(NAME) $(CL_KERNEL)

$(CL_KERNEL): $(CL_FILES)
	@$(call run_and_test, cat $(CL_FILES) > $@)

$(NAME): $(D_LIBS) $(P_OBJS) $(D_OBJS) $(D_UI_OBJS)
	@$(call run_and_test, $(CC) $(CFLAGS) -o $(NAME) $(D_OBJS) $(D_UI_OBJS) $(L_FLAGS) $(XML_LFLAGS) $(CL_LFLAG) $(GTK_LFLAGS))

$(P_OBJS)/%.o: $(P_SRCS)/%.c $(INC)
	@$(call run_and_test, $(CC) $(CFLAGS) $(I_FLAGS) $(XML_IFLAGS) $(GTK_IFLAGS) -o $@ -c $<)

$(P_OBJS)/%.o: $(P_UI_SRCS)/%.c $(INC)
	@$(call run_and_test, $(CC) $(CFLAGS) $(I_FLAGS) $(XML_IFLAGS) $(GTK_IFLAGS) -o $@ -c $<)

$(P_OBJS):
	@$(call run_and_test, mkdir -p $(P_OBJS))

$(D_LIBS):
	@$(call run_and_test, make -C $(dir $@))

clean:
	@$(call run_and_test, rm -rf $(P_OBJS) $(foreach LIB, $(LIBS),&& make -C $(basename $(LIB)) clean))

fclean: clean
	@$(call run_and_test, rm -f $(NAME) $(foreach LIB, $(LIBS),&& make -C $(basename $(LIB)) fclean) && rm -f $(CL_KERNEL))

re: fclean all
