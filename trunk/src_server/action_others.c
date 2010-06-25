/*
** action_others.c for zappy in /u/all/milbau_a/cu/vzappy
** 
** Made by alexis milbault
** Login   <milbau_a@epitech.net>
** 
** Started on  Thu Jun 17 16:37:29 2010 alexis milbault
** Last update Sun Jun 20 23:23:39 2010 alexis milbault
*/

#include "../includes/server.h"
#include "../includes/levels.h"

int	cmp_ressources(int *need, int *res)
{
  int	i;

  i = 0;
  while (res[i + 1])
    {
      if (res[i + 1] != need[i])
	return (-1);
      i++;
    }
  return (0);
}

int	check_lvl_up(t_desc *serv, t_play *player)
{
  int	id;
  t_map	*tmp;

  tmp = serv->map;
  id = 0;
  while (tmp && id == 0)
    {
      if ((tmp->x == player->x) && (tmp->y == player->y))
	id = 1;
      else
	tmp = tmp->next;
    }
  id = player->lvl - 1;
  if (tmp && (cmp_ressources(levels[id], tmp->res) == 0) &&
      get_players_on_map(serv->players, player->x, player->y) == levels[id][6])
    {
      add_sto_buffer(serv, "elevation en cours\n");
      write_to_client(serv, player->cs);
      return (0);
    }
  else
    {
      add_sto_buffer(serv, "ko\n");
      write_to_client(serv, player->cs);
      return (-1);
    }
}

void		lvl_up(t_desc *serv, t_play *player, t_env *e, char **cmd)
{
  int		id;
  t_map		*tmp;

  tmp = serv->map;
  id = 0;
  if (e->team && cmd[0])
    while (tmp && id == 0)
      {
	if ((tmp->x == player->x) && (tmp->y == player->y))
	  id = 1;
	else
	  tmp = tmp->next;
      }
  id = player->lvl - 1;
  if (tmp && (cmp_ressources(levels[id], tmp->res) == 0) &&
      get_players_on_map(serv->players, player->x, player->y) == levels[id][6])
    {
      player->lvl++;
      add_sto_buffer(serv, "niveau actuel : ");
      add_nto_buffer(serv, player->lvl);
      add_cto_buffer(serv, '\n');
    }
  else
    add_sto_buffer(serv, "ko\n");
  write_to_client(serv, player->cs);
}

void		connect_nbr(t_desc *serv, t_play *player, t_env *e, char **cmd)
{
  t_team	*tmp;
  int		flag;

  flag = 0;
  tmp = e->team;
  if (cmd[0] && serv->map)
    {
      while (tmp && (flag == 0))
	{
	  if (my_strcmp(player->team, tmp->name) == 0)
	    {
	      add_nto_buffer(serv, tmp->place);
	      add_cto_buffer(serv, '\n');
	      flag = 1;
	    }
	  tmp = tmp->next;
	}
      write_to_client(serv, player->cs);
    }
}
