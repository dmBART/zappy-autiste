/*
** action_objects.c for zappy in /u/all/milbau_a/cu/zappy
** 
** Made by alexis milbault
** Login   <milbau_a@epitech.net>
** 
** Started on  Wed Jun  2 15:06:26 2010 alexis milbault
** Last update Mon Jun 14 18:14:43 2010 aime-bijou iniongo
*/

#include "../includes/server.h"

void	inventory(t_desc *serv, t_play *player, char **cmd)
{
  int	i;
  int	len;
  int	start;

  i = -1;
  start = 0;
  if (serv && (cmd[0] != NULL))
    {
      while (++i < 7)
	{
	  len = my_strlen(get_ressource_name(i));
	  /*recuperation des ressources et mise dans le buffer*/
	  if (i == 6)
	    {
	      write(player->cs, (char *)get_ressource_name(i), len);
	      write(player->cs, " ", 1);
	      my_putnbr_fd(player->cs, player->inv[i]);
	      write(player->cs, "}\n", 2);
	    }
	  else
	    {
	      if (i == 0)
		write(player->cs, "{ ", 2);
	      write(player->cs, (char *)get_ressource_name(i), len);
	      write(player->cs, " ", 1);
	      my_putnbr_fd(player->cs, player->inv[i]);
	      write(player->cs, ", ", 2);
	    }
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
	  write(player->cs, "ok\n", 3);
	}
      else
	{
	  /*return KO to client*/
	  write(player->cs, "ok\n", 3);
	}
    }
  else
    {
      /*return KO to client*/
      write(player->cs, "ko\n", 3);
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
	  write(player->cs, "ok\n", 3);
	}
      else
	{	
	  /*return KO to client*/
	  write(player->cs, "ko\n", 3);
	}
    }
  else
    {
      /*return KO to client*/
      write(player->cs, "ko\n", 3);
    }
}
