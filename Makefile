NAME = philo
#-g -fsanitize=address
CC = gcc 
CFLAGS = -Wall -Wextra -Werror
FILES = main.c ft_atoi.c extra.c extra2.c
objets = $(FILES:.c=.o)

$(NAME):$(objets)
	$(CC) $(CFLAGS) -o $(NAME) $(FILES)

all :$(NAME)

clean :
	$(RM) $(objets) $(objets_b)

fclean : clean
	$(RM) $(NAME)

re : fclean all
#  github bigin
# git pull --rebase origin main
ADD = git add .

read :=	@echo "Add Commit Plz !!" && read -p "-> " enter \
		&& git commit -m $${enter}

PU = git push

commit = git log --graph --oneline --decorate HEAD^..HEAD

push :
	@$(commit)
	@$(ADD)
	$(read)
	$(PU)
