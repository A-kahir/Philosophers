CC = cc #-fsanitize=thread
CFLAGS = -Wall -Werror -Wextra -pthread

SRCS = main.c utils_func.c utils_philos.c ft_init.c ft_monitoring.c ft_action.c 

OBJS = $(SRCS:.c=.o)
OBJSB = $(SRCB:.c=.o)

NAME = philo
HEADER = philo.h

all : $(NAME)

%.o: %.c $(NAME)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS): %.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OBJB)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean 