CC=cc
CFLAGS=-Wall -Wextra -Werror -Ofast
NAME=fdf
OS := $(shell uname)
MLX_PATH=MLX42
INCLUDES=-I./includes -I MLX42/include/MLX42
MLX=libmlx42.a
MLX_FLAGS_LINUX=-Iinclude -ldl -lglfw -pthread -lm
MLX_FLAGS_MAC=  -framework Cocoa -framework OpenGL -framework IOKit -Iinclude -lglfw
MLX_FLAGS_LINUX =-I MLX42/include/MLX42 $(MLX) -Iinclude -ldl -lglfw -pthread -lm
#X11_FLAGS = -L/usr/X11/lib -lXext -lX11
ifeq ($(OS), Darwin)
	MLX_FLAGS = $(MLX_FLAGS_MAC)
else
	MLX_FLAGS = $(MLX_FLAGS_LINUX)
endif
LIBMLX=./MLX42
SOURCES= input.c utils1.c main.c line1.c line2.c draw.c color.c input_parser.c init_rgba.c projection.c utils2.c scaling_and_offset.c
OBJECTS = $(SOURCES:.c=.o)
LDFLAGS = -L./libft -libft
LIBFT_DIR = ./libft
LDFLAGS = -L./headers -libft -mlx
LIBFT = libft.a
LIBFT_PATH = $(LIBFT_DIR)/$(LIBFT)

all: $(NAME)

$(NAME): libmlx $(LIBFT_PATH) $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBFT) $(MLX) $(MLX_FLAGS) $(INCLUDES) -o $(NAME)

mac: $(NAME)

linux: $(LIBFT_PATH) $(OBJECTS) libmlx
	$(CC) $(OBJECTS) $(LIBFT) $(MLX) $(MLX_FLAGS_LINUX)


$(LIBFT_PATH):
	$(MAKE) -C $(LIBFT_DIR)
	cp $(LIBFT_PATH) $(LIBFT)

libft: $(LIBFT_PATH)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

all: libmlx $(NAME)

libmlx: $(LIBMLX)
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4
	cp MLX42/build/libmlx42.a $(MLX)
	cp MLX42/include/MLX42/MLX42.h includes/MLX42.h


a: $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -f $(OBJECTS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -rf $(LIBMLX)
	@rm -f $(NAME) $(LIBFT)
	@rm -f $(NAME) a.out
	@rm -rf $(LIBMLX)/build
	@$(MAKE) -C $(LIBFT_DIR) fclean


re: fclean all


norm:
	@norminette $(SOURCES) fdf.h
#$(LIBFT_DIR)

#install_brew:
#	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
#	~ gcc main.c ... libmlx42.a -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
$(LIBMLX):
	git clone https://github.com/codam-coding-college/MLX42.git

#$(LIBFT_DIR)


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
