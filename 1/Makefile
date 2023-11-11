CC=cc
#CFLAGS
NAME=fdf.a

#MLX_PATH=minilibx_macos
MLX_PATH=MLX42
MLX=libmlx42.a 
MLX_FLAGS= -framework Cocoa -framework OpenGL -framework IOKit libmlx42.a -Iinclude -lglfw -L"/Users/frapp/.brew/opt/glfw/lib/"
#MLX_FLAGS= -framework Cocoa -framework OpenGL -framework IOKit libmlx42.a -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
#MLX_FLAGS = -framework Cocoa -framework OpenGL -framework IOKit
#MLX_FLAGS = -Lminilibx_macos -lmlx -framework OpenGL -framework AppKit
X11_FLAGS = -L/usr/X11/lib -lXext -lX11

SOURCES= input.c utils1.c main.c utils_draw.c line1.c line2.c
OBJECTS = $(SOURCES:.c=.o)
LDFLAGS = -L./libft -libft
LIBFT_DIR = ./libft
LDFLAGS = -L./headers -libft -mlx
LIBFT = libft.a
LIBFT_PATH = $(LIBFT_DIR)/$(LIBFT)


all: $(NAME) clean

$(NAME): libft $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBFT) $(MLX_FLAGS)
#$(CC) testin1.c $(MLX) $(LIBFT) $(MLX_FLAGS)  $(MLX)

#$(CC) $(MLX_FLAGS) $(X11_FLAGS)

$(LIBFT_PATH):
	$(MAKE) -C $(LIBFT_DIR)
	cp $(LIBFT_PATH) $(LIBFT)

libft: $(LIBFT_PATH)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:

	rm -f $(OBJECTS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(LIBFT)
	rm -f a.out
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all




# NAME	:= Game
# CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
# LIBMLX	:= ./lib/MLX42

# HEADERS	:= -I ./include -I $(LIBMLX)/include
# LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
# SRCS	:= $(shell find ./src -iname "*.c")
# OBJS	:= ${SRCS:.c=.o}

# all: libmlx $(NAME)

# libmlx:
# 	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

# %.o: %.c
# 	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

# $(NAME): $(OBJS)
# 	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

# clean:
# 	@rm -rf $(OBJS)
# 	@rm -rf $(LIBMLX)/build

# fclean: clean
# 	@rm -rf $(NAME)

# re: clean all

# .PHONY: all, clean, fclean, re, libmlx
