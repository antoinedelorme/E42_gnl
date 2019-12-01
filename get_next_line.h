#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H 
#include<strings.h>
#include <stdlib.h>
#define BUFF_SIZE 10000


	typedef struct s_data
{
	char	*content;
	size_t	position;
	size_t	offset;
	size_t	size;
	int	eof;
} t_data;

void strdel(char **pointer)
{
	free(*pointer);
	*pointer = NULL;
}

char *strnew(size_t size)
{
	char *temp;

	temp = (char*)malloc(size + 1);
	bzero(temp, size + 1);
	return(temp);
}

void *memnew(size_t size)
{
	void *temp;

	temp = malloc(size);
	bzero(temp, size);
	return(temp);
}

void memdel(void **pointer)
{
	free(*pointer);
	*pointer = NULL;
}

#endif
