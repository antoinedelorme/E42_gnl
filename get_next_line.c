#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"
#include <string.h>
#include <strings.h>
//#include "libft.h"
// MUST REMOVE STRING

 
int testLine(t_data *data)
{
    size_t i;
        
    i = data->offset;
    while (i < data->size)
    {
        if (data->content[i] == '\n')
        {
            data->offset = i;
            return (1);
        }
        i++;
    }
    if (data->eof)
        data->offset = data->size;
    return (0);
}
 
int extract(char **line, t_data **data)
{
    char *temp;
    size_t size;
    int flag;
    int result;

    flag = ((*data)->offset == (*data)->size);
    if ((result = ((*data)->size == 0) ? 0 : 1) || !(*data)->eof)
    {
        size = (*data)->offset - (*data)->position;
        temp = strnew(size);
        memmove(temp, ((*data)->content + (*data)->position), size);
        (*data)->position = (*data)->position + size + 1;
        *line = temp;

        (*data)->offset = (*data)->position;
        testLine(*data);
    }
        

     if(flag)
    {
        strdel(&(*data)->content);
        memdel((void**) data);
        *data = NULL;
    }
    return (result);
}
 
int append(t_data **dest, char *buf, size_t size)
{
    char *content;

    content = (char *)malloc(sizeof(char) * (size + (*dest)->size));
    memmove(content, (*dest)->content, (*dest)->size);
    memmove(content + (*dest)->size, buf, size);
    (*dest)->size = (*dest)->size + size;
    
    if ((*dest)->content)
        strdel((&((*dest)->content)));
    (*dest)->content = content;
    return (0);
}
 
int clean_content(t_data **data)
{
    char *temp;
    size_t size;
    size_t new_size;

    if (!(*data))
    {
        *data = (t_data *)memnew(sizeof(t_data));
        return (1);
    }
    if ((*data)->position == (*data)->offset)
        {
            new_size = (*data)->size - (*data)->offset;
            temp = strnew(new_size);
            memmove(temp, ((*data)->content + (*data)->offset), new_size);
            strdel(&((*data)->content));
            (*data)->content = temp;
            (*data)->position = 0;
            (*data)->offset = 0;
            (*data)->size = new_size;
            return (1);
   
    }
    return (0);
}
 
int get_next_line(const int fd, char **line)
{
    char buff[BUFF_SIZE];
    size_t readSize;
    static t_data *lb;

    if (!lb || lb->position == lb->offset)
    {
        clean_content(&lb);
        while(!testLine(lb) && !lb->eof)
        {   
            readSize = read(fd, buff, BUFF_SIZE );
            if ((lb->eof = (readSize  <  BUFF_SIZE) ? 1 : 0))
                testLine(lb);
            append(&lb, buff, readSize);
            
        }
    }
    return (extract(line, &lb));
}
