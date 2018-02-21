/*
** get_next_line.h for get_next_line in /home/alkoleek/CPE_2016_getnextline
** 
** Made by Maxime DROUIN
** Login   <alkoleek@epitech.net>
** 
** Started on  Fri Jan  6 13:54:24 2017 Maxime DROUIN
** Last update Mon Jan 16 20:16:10 2017 Maxime DROUIN
*/

#ifndef GET_NEXT_LINE_
# define GET_NEXT_LINE_
typedef struct s_element t_element;
struct s_element
{
  char           val;
  struct s_element *nxt;
};
typedef t_element* t_llist;
t_llist	add_last(t_llist, char);
t_llist	del_first(t_llist);
char	*conv_llist(t_llist, t_llist);
char	*llist_to_array(t_llist, int, int, const int);
char	*get_next_line(const int);
#ifndef READ_SIZE
# define READ_SIZE (300)
#endif /* !READ_SIZE */
#endif /* !MY_H_ */
