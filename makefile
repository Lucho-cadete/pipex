# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luimarti <luimarti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/09 15:17:20 by luimarti          #+#    #+#              #
#    Updated: 2025/11/14 17:39:33 by luimarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_BONUS = pipex_bonus
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
			tools_for_bonus.c \
			heredoc.c \
			get_next_line.c \
			get_next_line_utils.c

OBJ_DIR = o_files
MANDATORY_OBJ = $(addprefix $(OBJ_DIR)/, $(MANDATORY_SRC:.c=.o))
BONUS_OBJ = $(addprefix $(OBJ_DIR)/, $(BONUS_SRC:.c=.o))

RM = rm -f

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(MANDATORY_OBJ)
	$(CC) $(CFLAGS) $(MANDATORY_OBJ) -o $(NAME)

$(NAME_BONUS): $(BONUS_OBJ)
	$(CC) $(CFLAGS) $(BONUS_OBJ) -o $(NAME_BONUS)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(RM) -r $(OBJ_DIR)
	@echo "🧹 Object files removed"

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)
	@echo "🗑️  Full clean done"

re: fclean all

.PHONY: all clean fclean re bonus

