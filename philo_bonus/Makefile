# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bkamal <bkamal@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/19 00:31:19 by bkamal            #+#    #+#              #
#    Updated: 2023/01/08 20:16:30 by bkamal           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo_bonus

SRCB	= philo_bonus.c\
			error_bonus.c\
			ops_bonus.c\
			timefuncs.c\
			utils.c

OBJB	= $(SRCB:.c=.o)

CFLAGS	= -Wall -Wextra -Werror

RM		= rm -f

$(NAME): $(OBJB)
	$(CC) $(CFLAGS) $(OBJB) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS) $(OBJB)

fclean: clean
	$(RM) $(NAME) $(BONUS)

re: fclean all

.PHONY: all clean fclean re