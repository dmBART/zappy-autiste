/*
** action_duplicate.c for zappy in /u/all/milbau_a/cu/zop
** 
** Made by alexis milbault
** Login   <milbau_a@epitech.net>
** 
** Started on  Sun Jun 20 15:30:24 2010 alexis milbault
** Last update Sun Jun 20 16:33:31 2010 alexis milbault
*/

#include "../includes/server.h"

void	init_egg(t_desc *serv, t_play *player, t_play *cur, int i)
{
  int	j;

  j = 0;
  player[i].life = 1260;
  player[i].type = FD_GHOST;
  player[i].end = 0;
  player[i].state = 0;
  player[i].begin = 0;
  player[i].lvl = 1;
  place_joueur_on_the_map(player[i], serv);
  player[i].inv = xmalloc(sizeof(int *) * 7);
  while (j < 7)
    {
      if (j == 0)
	player[i].inv[j] = 10;
      else
	player[i].inv[j] = 0;
      i++;
    }
}

void	add_player(t_desc *serv, t_play *players, t_play *cur)
{
  int	i;

  i = 0;
  while (i < MAX_FD)
    {
      if (players[i].type == FD_FREE)
	{
	  init_egg(serv, players, cur, i);
	  break;
	}
      i++;
    }
}

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
	      add_player(serv, serv->players, player);
	      break;
	    }
	  else
	    tmp = tmp->next;
	}
      add_to_buffer(serv, "ok\n");
      write_to_client(serv, player->cs);
    }
}
