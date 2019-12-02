#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H 
#include<strings.h>
#include <stdlib.h>
#define BUFF_SIZE 2


	typedef struct s_data
{
	char	*cnt;
	size_t	pos;
	size_t	nxt;
	size_t	size;
	int error;
	int	eof;
} t_data;

#endif
