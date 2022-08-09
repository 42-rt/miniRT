# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/01 15:07:16 by jkong             #+#    #+#              #
#    Updated: 2022/08/01 15:07:16 by jkong            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SUFFIXES: .c .o .h
.PHONY: all clean fclean re

CC = cc
RM = rm -f

OBJECTS_DIR = objs/

HEADER = rt.h
SOURCE = program.c rt_draw.c \
			rt_parse.c rt_format.c rt_format_vector.c \
			rt_input.c rt_input_key.c rt_input_mouse.c rt_input_move.c \
			rt_vector.c rt_vector3.c
OBJECT = $(addprefix $(OBJECTS_DIR), $(SOURCE:.c=.o))

HEADER_LIBFT = libft.h
SOURCE_LIBFT = libft_memory.c libft_string.c
OBJECT_LIBFT = $(addprefix $(OBJECTS_DIR), $(SOURCE_LIBFT:.c=.o))

HEADER_GNL = get_next_line.h
SOURCE_GNL = get_next_line.c get_next_line_utils.c
OBJECT_GNL = $(addprefix $(OBJECTS_DIR), $(SOURCE_GNL:.c=.o))

SOURCE_GENERAL = util_flag.c safe_io.c safe_io_utils.c safe_mem.c \
					util_try_atoi.c util_try_atof.c \
					generic_list.c
OBJECT_GENERAL = $(addprefix $(OBJECTS_DIR), $(SOURCE_GENERAL:.c=.o))

SOURCE_PARSER = parser.c parser_utils.c parser_reduce.c parser_state.c \
					parser_lex.c parser_syntax.c parser_entry.c parser_format.c
OBJECT_PARSER = $(addprefix $(OBJECTS_DIR), $(SOURCE_PARSER:.c=.o))

TARGET = miniRT
OBJS = $(OBJECT) $(OBJECT_LIBFT) $(OBJECT_GNL) \
		$(OBJECT_GENERAL) $(OBJECT_PARSER)

MLX = mlx
ifeq ($(shell uname), Linux)
	MLX_TYPE = a
	MLX_DIR = minilibx-linux
	MLX_DEP = -lXext -lX11
else
	MLX_TYPE = dylib
	MLX_DIR = minilibx_mms_20210621
	MLX_HOOK = OPTI=-Ounchecked
endif
MLX_NAME = lib$(MLX).$(MLX_TYPE)

LDFLAGS += -lm
CFLAGS += -I$(MLX_DIR)
LDFLAGS += -L$(MLX_DIR) -l$(MLX) $(MLX_DEP)

C_SANITIZER_FLAGS = #address undefined
CFLAGS += $(addprefix -fsanitize=, $(C_SANITIZER_FLAGS))
LDFLAGS += $(addprefix -fsanitize=, $(C_SANITIZER_FLAGS))

C_WARNING_FLAGS = all extra error
CFLAGS += $(addprefix -W, $(C_WARNING_FLAGS))

C_DEBUG_FLAGS = g3
CFLAGS += $(addprefix -, $(C_DEBUG_FLAGS))

all: $(TARGET)
clean: dclean		;	$(RM) -r $(OBJECTS_DIR)
fclean: clean		;	$(RM) $(TARGET)
re: fclean			;	$(MAKE) all
bonus: all

$(OBJECTS_DIR):
	mkdir $(OBJECTS_DIR)

$(OBJS): | $(OBJECTS_DIR)

$(addprefix $(OBJECTS_DIR), %.o): %.c
	$(CC) $(INCLUDE) -c $< -o $@ $(CFLAGS)

$(TARGET): $(OBJS) | $(MLX_NAME)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJECT): $(HEADER)

$(OBJECT_LIBFT): $(HEADER_LIBFT)
$(OBJECT_GNL): $(HEADER_GNL)

$(OBJECT_PARSER): parser.h
$(addprefix $(OBJECTS_DIR), util_flag.o): util_flag.h
$(addprefix $(OBJECTS_DIR), util_try_atoi.o): util_try_atoi.h
$(addprefix $(OBJECTS_DIR), util_try_atof.o): util_try_atof.h
$(addprefix $(OBJECTS_DIR), safe_io.o safe_io_utils.o): safe_io.h
$(addprefix $(OBJECTS_DIR), safe_mem.o): safe_mem.h
$(addprefix $(OBJECTS_DIR), generic_list.o): generic_list.h

dclean:
	$(RM) $(MLX_NAME)
	$(MAKE) -C $(MLX_DIR) clean

release: C_SANITIZER_FLAGS=
release: C_DEBUG_FLAGS=
release: CFLAGS+=-O3
release: all

$(MLX_NAME):
	$(MAKE) -C $(MLX_DIR) all $(MLX_HOOK)
	cp $(MLX_DIR)/$(MLX_NAME) .
