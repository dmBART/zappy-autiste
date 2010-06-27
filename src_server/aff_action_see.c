/*
** aff_action_see.c for zappy in /u/all/milbau_a/cu/zop
** 
** Made by alexis milbault
** Login   <milbau_a@epitech.net>
** 
** Started on  Sun Jun 20 18:20:39 2010 alexis milbault
** Last update Sun Jun 20 18:42:32 2010 alexis milbault
*/

#include "../includes/server.h"

int	get_players_on_map(t_play *players, int x, int y)
{
  int	i;
  int	count;

  i = 0;
  count = 0;
  while (players[i].team != NULL)
    {
      if ((players[i].x == x) && (players[i].y == y))
	count++;
      i++;
    }
  return (count);
}

void	aff_player_on_case(t_desc *serv, int x, int y)
{
  int	i;
  int	flag;

  flag = 0;
  i = get_players_on_map(serv->players, x, y) + 1;
  while (--i > 0)
    {
      if (flag == 1)
	add_cto_buffer(serv, ' ');
      add_sto_buffer(serv, "joueur");
      flag = 1;
    }
}

void	aff_ressources_on_case(t_desc *serv, int x, int y)
{
  t_map	*tmp;
  int	i;
  int	j;

  tmp = serv->map;
  i = -1;
  while (tmp)
    {
      if ((tmp->x == x) && (tmp->y == y))
	while (++i < 7)
	  {
	    j = tmp->res[i] + 1;
	    while (--j > 0)
	      {
		add_cto_buffer(serv, ' ');
		add_sto_buffer(serv, (char *)get_ressource_name(i));
	      }
	  }
      tmp = tmp->next;
    }
}

void	aff_case(t_desc *serv, int x, int y)
{
  aff_player_on_case(serv, x, y);
  aff_ressources_on_case(serv, x, y);
}
