/*
** action_objects.c for zappy in /u/all/milbau_a/cu/zappy
** 
** Made by alexis milbault
** Login   <milbau_a@epitech.net>
** 
** Started on  Wed Jun  2 15:06:26 2010 alexis milbault
** Last update Thu Jun 10 18:57:22 2010 alexis milbault
*/

#include "../includes/server.h"

void	inventory(t_desc *serv, t_play *player, char **cmd)
{
  int	i;

  i = -1;
  if (serv && (cmd[0] != NULL))
    {
      while (++i < 7)
	{
	  /*recuperation des ressources et mise dans le buffer*/
	}    
    }
}

void	take_object(t_desc *serv, t_play *player, char **cmd)
{
  int	id;

  if ((cmd[1] != NULL) && ((id = get_ressource_id(cmd[1])) >= 0))
    {
      if (take_ressource_on_map(serv->map, player->x, player->y, id) == 0)
	{
	  player->inv[id]++;
	  /*return OK to client*/
	}
      else
	{
	  /*return KO to client*/
	}
    }
  else
    {
      /*return KO to client*/
    }
}

void	drop_object(t_desc *serv, t_play *player, char **cmd)
{
  int	id;

  if ((cmd[1] != NULL) && ((id = get_ressource_id(cmd[1]) >= 0)))
    {
      if (player->inv[id] > 0)
	{
	  player->inv[id]--;
	  if (update_exist_case(serv->map, player->x, player->y, id) < 0)
	    fill_map(&serv->map, player->x, player->y, id);
	  /*return OK to client*/
	}
      else
	{	
	  /*return KO to client*/
	}
    }
  else
    {
      /*return KO to client*/
    }
}