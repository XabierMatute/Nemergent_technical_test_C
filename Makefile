NAME := technical_test

SRC :=	main.c 

HEADER := technical_test.h
		
WHITE = \033[0;37m
RED = \033[0;31m
CYAN = \033[0;36m
GREEN = \033[0;32m
MAGENTA = \033[0;35m

OBJ := $(SRC:%.c=%.o)

SANI 	:= -fsanitize=address -g3

CC 		:= gcc
CFLAGS 	:= -Wall -Wextra -Werror

CFLAGS	:= $(CFLAGS) $(EFLAGS)

RM 		:= rm -rf

TESTER := test.py

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled...$(WHITE)"

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

sani:
	$(MAKE) EFLAGS='$(SANI)' all

flagless:
	$(MAKE) CFLAGS='' all

test: all $(TESTER)
	python3 $(TESTER) ./$(NAME)


clean : 
		$(RM) $(OBJ)
		@echo "$(RED)clean done...$(WHITE)"

fclean : clean
		$(RM) $(NAME)
		@echo "$(RED)fclean done...$(WHITE)"

re : fclean all

.PHONY : all clean fclean re sani flagless test