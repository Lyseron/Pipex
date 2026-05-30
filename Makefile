NAME       = pipex
CC         = cc
CFLAGS     = -Wall -Wextra -Werror -g

INCS	   = -I. -I$(LIBFT_DIR)

LIBFT_DIR  = libft

LIBFT      = $(LIBFT_DIR)/libft.a

SRCS    = path_utils.c path.c cmd_utils.c cmd_1.c cmd_2.c main.c

OBJS    = $(SRCS:%.c=%.o)
RM      = rm -f

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re