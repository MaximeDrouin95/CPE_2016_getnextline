/*
** get_next_line.c for get_next_line in /home/alkoleek
** 
** Made by Maxime DROUIN
** Login   <alkoleek@epitech.net>
** 
** Started on  Thu Jan  5 15:04:24 2017 Maxime DROUIN
** Last update Mon Jan 16 20:16:36 2017 Maxime DROUIN
*/

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

static int g_eof = 0;

t_llist   add_last(t_llist list, char val)
{
  t_llist new_list;
  t_llist temp;

  temp = list;
  new_list = malloc(sizeof(t_element));
  new_list->val = val;
  new_list->nxt = NULL;
  if (list == NULL)
    return (new_list);
  else
    while (temp->nxt != NULL)
      temp = temp->nxt;
  temp->nxt = new_list;
  return (list);
}

t_llist		del_first(t_llist list)
{
  t_llist	new_list;

  new_list = list->nxt;
  if (list != NULL)
    {
      free(list);
      return (new_list);
    }
  else
    return (NULL);
}

char	*conv_llist(t_llist list, t_llist temp)
{
  int	count;
  char	*array;
  int	i;

  i = 0;
  count = 0;
  while (temp->val != '\n')
    {
      temp = temp->nxt;
      count = count + 1;
    }
  array = malloc(sizeof(char) * count + 1);
  while (list->val != '\n')
    {
      array[i] = list->val;
      list = list->nxt;
      i = i + 1;
    }
  array[i] = '\0';
  return (array);
}

char			*llist_to_array(t_llist list, int i, int count, const int fd)
{
  char			*array;
  static t_llist	list_static = NULL;
  t_llist		temp;

  if (i < READ_SIZE && g_eof == 0 && count != 0 && fd != 0)
    {
      g_eof = 1;
      list = add_last(list, '\n');
    }
  while (list != NULL)
    {
      list_static = add_last(list_static, list->val);
      list = del_first(list);
    }
  if (list_static == NULL)
    return (NULL);
  temp = list_static;
  array = conv_llist(list_static, temp);
  while (list_static->val != '\n')
    list_static = del_first(list_static);
  if (list_static->val == '\n')
    list_static = del_first(list_static);
  return (array);
}

char		*get_next_line(const int fd)
{
  char		*buffer;
  t_llist	line;
  int		count;
  int		i;
  int		end;

  line = NULL;
  end = 0;
  buffer = malloc(sizeof(char) * (READ_SIZE + 1));
  while (end != -1 && (i = read(fd, buffer, READ_SIZE)) > 0)
    {
      count = 0;
      buffer[i]  = '\0';
      while (buffer[count] != '\0')
	{
	  if (buffer[count] == '\n')
	    {
	      end = -1;
	      g_eof = 1;
	    }
	  line = add_last(line, buffer[count]);
	  count = count + 1;
	}
    }
  free(buffer);
  return (llist_to_array(line, i, count, fd));
}
