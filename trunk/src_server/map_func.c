/*
** map_func.c for zappy in /u/all/milbau_a/cu/zappy
** 
** Made by alexis milbault
** Login   <milbau_a@epitech.net>
** 
** Started on  Thu Jun  3 14:49:09 2010 alexis milbault
** Last update Thu Jun  3 15:02:37 2010 alexis milbault
*/

#include "../includes/server.h"

void	update_ressource(t_map *map, int i)
{
  if (i == 0)
    map->food++;
  if (i == 1)
    map->lin++;
  if (i == 2)
    map->der++;
  if (i == 3)
    map->sib++;
  if (i == 4)
    map->men++;
  if (i == 5)
    map->phi++;
  if (i == 6)
    map->thy++;
}

void	tzero_map(t_map *new)
{
  new->food = 0;
  new->lin = 0;
  new->der = 0;
  new->sib = 0;
  new->men = 0;
  new->phi = 0;
  new->thy = 0;
}

void	fill_map(t_map **map, int x, int y, int i)
{
  t_map		*new;

  new = xmalloc(sizeof(*new));
  tzero_map(new);
  new->x = x;
  new->y = y;
  update_ressource(new, i);
  new->next = *map;
  *map = new;
}
