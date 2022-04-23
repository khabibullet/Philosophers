# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/11 21:25:23 by anemesis          #+#    #+#              #
#    Updated: 2022/04/23 15:21:36 by anemesis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo/philo

NAME_B		=	philo_bonus/philo_bonus

HEADER		=	philo/inc/philo.h

HEADER_B	=	philo_bonus/inc/philo_bonus.h

SRCDIR		=	philo/src

SRCDIR_B	=	philo_bonus/src

OBJDIR		=	philo/obj

OBJDIR_B	=	philo_bonus/obj

SRC			=	$(wildcard $(SRCDIR)/*.c)

SRC_B		=	$(wildcard $(SRCDIR_B)/*.c)

OBJ			=	$(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

OBJ_B		=	$(SRC_B:$(SRCDIR_B)/%.c=$(OBJDIR_B)/%.o)

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJ) $(HEADER)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

bonus : $(NAME_B)

$(NAME_B) : $(OBJ_B) $(HEADER_B)
	@$(CC) $(CFLAGS) $(OBJ_B) -o $(NAME_B)

$(OBJDIR_B)/%.o : $(SRCDIR_B)/%.c
	@mkdir -p $(OBJDIR_B)
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@rm -rf $(OBJDIR) $(OBJDIR_B)

fclean : clean
	@rm -f $(NAME) $(NAME_B)

re : fclean all bonus

.PHONY : all bonus clean fclean re
