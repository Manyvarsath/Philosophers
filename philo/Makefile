# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bkamal <bkamal@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/19 00:31:19 by bkamal            #+#    #+#              #
#    Updated: 2023/01/08 20:15:09 by bkamal           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

SRCM	= philo.c\
			errors.c\
			utils.c\
			timefuncs.c\
			threads.c
			
OBJS	= $(SRCM:.c=.o)

CFLAGS	= -Wall -Wextra -Werror

RM		= rm -f

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS) $(OBJB)

fclean: clean
	$(RM) $(NAME) $(BONUS)

re: fclean all

.PHONY: all clean fclean re