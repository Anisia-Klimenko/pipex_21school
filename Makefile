NAME	=	pipex

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror

OBJDIR	=	obj
SRCDIR	=	src
LIBDIR	=	libft

HEADER	=	pipex.h

SRC		=	$(SRCDIR)/main.c	\
			$(SRCDIR)/utils.c

OBJ		=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))

LIBFT	=	libft.a

.PHONY	:	all clean fclean re bonus

all		:	$(NAME)

$(NAME)	:	$(OBJ)
			@make -C $(LIBDIR)/
			@cp $(LIBDIR)/$(LIBFT) ./
			@printf "\n\t\033[92m \xE2\x9C\x94 LIBFT compiled!\033[92m\n\n"
			@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
			@printf "\t\033[92m \xE2\x9C\x94 PIPEX compiled!\033[92m \n\n"

$(OBJDIR)/$(SRCDIR)/%.o: 	$(SRCDIR)/%.c $(HEADER)
				@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR) :
	@mkdir $@ $@/$(SRCDIR)

$(OBJ) : | $(OBJDIR)

clean:
	@printf "clean... \n"
	@make fclean -C $(LIBDIR)/
	@rm -rf $(OBJDIR)

fclean: clean
	@printf "fclean... \n"
	@rm -rf $(NAME)
	@rm -f $(LIBFT)

re: fclean all

# color:	
# 	@echo "\033[92mHello World\033[0m"
# 	@echo "\033[0;1;31mHello World\033[0;1;31m"