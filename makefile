# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luimarti <luimarti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/09 15:17:20 by luimarti          #+#    #+#              #
#    Updated: 2025/11/14 12:16:04 by luimarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

vpath %.c pipex

NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror

MANDATORY_SRC = main.c \
				ft_split.c \
				libft.c \
				tools.c \
				error_managing.c \
				find_command.c \
				libft2.c

BONUS_SRC = main_bonus.c \
			ft_split.c \
			libft.c \
			tools.c \
			error_managing.c \
			find_command.c \
			libft2.c \
			heredoc.c \
			pipes_bonus.c

OBJ_DIR = o_files
MANDATORY_OBJ = $(addprefix $(OBJ_DIR)/, $(MANDATORY_SRC:.c=.o))
BONUS_OBJ = $(addprefix $(OBJ_DIR)/, $(BONUS_SRC:.c=.o))

RM = rm -f

all: $(NAME)

bonus: $(BONUS_OBJ)
	$(CC) $(CFLAGS) $(BONUS_OBJ) -o $(NAME)

$(NAME): $(MANDATORY_OBJ)
	$(CC) $(CFLAGS) $(MANDATORY_OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(RM) -r $(OBJ_DIR)
	@echo "🧹 Object files removed"

fclean: clean
	$(RM) $(NAME)
	@echo "🗑️  Full clean done"

re: fclean all

.PHONY: all clean fclean re bonus
