# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nradin <nradin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/14 13:37:00 by nradin            #+#    #+#              #
#    Updated: 2023/03/05 14:37:05 by nradin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	main.c			\
		parse_utils.c	\

NAME = philo

OBJS_DIR = objs/

OBJS = $(SRCS:.c=.o)
OBJECTS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))

CC = gcc

CC_FLAGS = -Wall -Wextra -Werror

$(OBJS_DIR)%.o : %.c philo.h
	@mkdir -p $(OBJS_DIR)
	@echo "Compiling: $<"
	@gcc $(CC_FLAGS) -c $< -o $@

$(NAME): $(OBJECTS_PREFIXED)
	@gcc -o $(NAME) $(OBJECTS_PREFIXED)

all: $(NAME)

clean:
	@rm -rf $(OBJS_DIR)


fclean: clean
	@rm -f $(NAME)

re: fclean all
