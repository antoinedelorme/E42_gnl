#include <fcntl.h>
#include <unistd.h>

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"

//#include "get_next_line.h"
#include <stdio.h>
int get_next_line(const int fd, char **line);
int main()
{
	int fd;
	char *line;
	int i;

	fd = open("test.txt",O_RDONLY);

	i =0;

	while (get_next_line(fd, &line) && i<10)
	{
		printf(KYEL);
		printf("%i :\t",i);
		printf("%s\n", line);
		printf(KNRM);
		i++;
		
	}
	close (fd);
}

