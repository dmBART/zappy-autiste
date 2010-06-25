/*
** map_func.c for zappy in /u/all/milbau_a/cu/zappy
** 
** Made by alexis milbault
** Login   <milbau_a@epitech.net>
** 
** Started on  Thu Jun  3 14:49:09 2010 alexis milbault
** Last update Sun Jun 20 23:38:43 2010 alexis milbault
*/

#include "../includes/server.h"

typedef struct	s_res
{
  char		*res;
  int		id;
}		t_res;

t_res	res_tab[]= {
  {"nourriture", 0},
  {"linemate", 1},
  {"deraumere", 2},
  {"sibur", 3},
  {"mendiane", 4},
  {"phiras", 5},
  {"thystame", 6},
};

char	*get_ressource_name(int id)
{
  return (res_tab[id].res);
}

int	get_ressource_id(char *res)
{
  int	i;

  i = 0;
  while (i < 7)
    {
      if (my_strcmp(res_tab[i].res, res) == 0)
	return (res_tab[i].id);
      i++;
    }
  return (-1);
}

int	take_ressource_on_map(t_map *map, int x, int y, int id)
{
  t_map	*tmp;

  tmp = map;
  while (tmp)
    {
      if ((tmp->x == x) && (tmp->y == y))
	{
	  if (tmp->res[id] > 0)
	    {
	      tmp->res[id]--;
	      return (0);
	    }
	  return (-1);
	}
      tmp = tmp->next;
    }
  return (-1);
}

int	update_exist_case(t_map *map, int x, int y, int id)
{
  t_map	*tmp;

  tmp = map;
  while (tmp)
    {
      if ((tmp->x == x) && (tmp->y == y))
	{
	  tmp->res[id]++;
	  return (0);
	}
      tmp = tmp->next;
    }
  return (-1);
}

void	tzero_map(t_map *new)
{
  int	i;

  i = 0;
  while (i < 7)
    new->res[i++] = 0;
}

void	fill_map(t_map **map, int x, int y, int id)
{
  t_map		*new;

  new = xmalloc(sizeof(*new));
  tzero_map(new);
  new->x = x;
  new->y = y;
  new->res[id]++;
  new->next = *map;
  *map = new;
}
