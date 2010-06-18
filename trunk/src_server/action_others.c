/*
** action_others.c for zappy in /u/all/milbau_a/cu/vzappy
** 
** Made by alexis milbault
** Login   <milbau_a@epitech.net>
** 
** Started on  Thu Jun 17 16:37:29 2010 alexis milbault
** Last update Fri Jun 18 03:53:09 2010 alexis milbault
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
      (get_players_on_map(serv->players, player->x, player->y) == levels[id][6]))
    {
      player->lvl++;
      write(player->cs, "niveau actuel : ", 16);
      my_putnbr_fd(player->cs, player->lvl);
      write(player->cs, "\n", 1);
    }
  else
    write(player->cs, "ko\n", 3);
}
/*
void		duplicate_player(t_desc *serv, t_play *player, t_env *e, char **cmd)
{
  t_team	*tmp;

  tmp = e->team;
  if (cmd[0])
    {
      while (tmp)
	{
	  if (my_strcmp(player->team, tmp->name) == 0)
	    {
	      
	    }
	  else
	    tmp = tmp->next;
	}
    }
}
*/
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
	      my_putnbr_fd(player->cs, tmp->place);
	      write(player->cs, "\n", 1);
	      flag = 1;
	    }
	  tmp = tmp->next;
	}
    }
}
