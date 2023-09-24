
NAME = libft.a
SOURCES = ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strrchr.c ft_tolower.c ft_toupper.c ft_strnstr.c ft_strdup.c ft_itoa.c ft_atoi.c ft_strtrim.c ft_split.c ft_substr.c ft_calloc.c ft_bzero.c ft_strjoin.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_striteri.c ft_strmapi.c
OBJECTS = $(SOURCES:%.c=%.o)
BONUSS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c #ft_lstclear.c ft_lstiter.c ft_lstmap.c
BONUSO = $(BONUSS:%.c=%.o)
CC = cc
CFLAGS = -Wall -Werror -Wextra

all:	$(NAME)

$(NAME):	$(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(CC) -g $(CFLAGS) -c $(SOURCES)


bonus: fclean
	$(CC) $(CFLAGS) -g -c $(SOURCES) $(BONUSS)
	ar rcs $(NAME) $(OBJECTS) $(BONUSO)

clean:
	rm -f $(OBJECTS) $(BONUSO)

fclean:	clean
	rm -f $(NAME)
	# oder: rm libft.a -> löscht .a library file

re:	fclean all

.PHONY:	all clean fclean re bonus
