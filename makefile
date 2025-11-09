# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luimarti <luimarti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/09 15:17:20 by luimarti          #+#    #+#              #
#    Updated: 2025/11/09 15:31:08 by luimarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

vpath %.c pipex

NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror
FILES = ft_split.c \
		tools.c \
		read_write.c \
		pipex_main.c 
OBJ_DIR = o_files
OBJS = $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))
RM = rm -f

all: $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME):$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@echo "🧹 Object files removed!"
	@$(RM) $(OBJS)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "🗑️  Full clean done!"
	@$(RM) $(NAME)

re: fclean all
	@echo "🔁 Rebuilding project..."

.PHONY: all clean fclean re