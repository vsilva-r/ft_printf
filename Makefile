# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsilva-r <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/07 18:04:23 by vsilva-r          #+#    #+#              #
#    Updated: 2024/05/07 18:04:24 by vsilva-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = cc
CFLAGS = -Wall -Werror -Wextra

LIBFT = ./libft/libft.a

SRCS = ft_printf.c
				
OBJS := $(SRCS:%.c=objs/%.o)

.PHONY = all clean fclean re bonus

all : ${NAME}

$(NAME): ${LIBFT} ${OBJS}
	@echo -n "Linking archive... "
	@cp ${LIBFT} ${NAME} 
	@ar rs ${NAME} ${OBJS}
	@echo "Done."
	
${LIBFT}: 
	@echo "Making libft library... "
	@make -C libft
	@echo "Done."

$(OBJS): $(SRCS) ${LIBFT}
	@echo -n "Creating objects... "
	@mkdir -p objs
	@cc ${CFLAGS} ${SRCS} -c
	@mv *.o objs
	@echo "Done."

clean:
	@echo -n "Cleaning objects... "
	@rm -rf *.o *.gch objs
	@echo "Done."
	
fclean: clean
	@echo -n "Cleaning archives... "
	@rm -rf ${NAME} .bonus
	@make fclean -C libft
	@echo "Done."

re: fclean all
