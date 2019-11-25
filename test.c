#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"
#include "libft.h"
#include <stdlib.h>
#include <fcntl.h>


int get_next_line(const int fd, char **line);


int     main(int ac, char **av)
{
   char     *str;
   int      fd;
   size_t   number;
   int      result;
   
   free(NULL);

   number =0;
   (void) ac;
   (void) av;
   
   str = NULL;
   fd = open (av[1], O_RDONLY);
   //fd = 0;
   while((result = get_next_line(fd, &str) == 1))
   {
   ft_putstr("--LINE READ ");
   ft_putstr(ft_itoa(number));
   ft_putstr(" :\t");
   
   ft_putstr(str);
   ft_putstr("||\t || result: ");
   ft_putstr(ft_itoa(result));
   ft_putstr("\n");
   ft_strdel(&str);
   number++;
   }
   
   
   //ft_putstr(str);
   
   return (0);
}

