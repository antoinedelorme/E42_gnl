gcc -fsanitize=address -Wall -Wextra -Werror -I./libft/ -L./libft/ -lft get_next_line.c test.c && ./a.out $1
