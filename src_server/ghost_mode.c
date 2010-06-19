/*
** ghost_mode.c for ghost mode in /u/all/iniong_a/cu/rendu/c/trunk/src_server
** 
** Made by aime-bijou iniongo
** Login   <iniong_a@epitech.net>
** 
** Started on  Sat Jun 19 18:02:32 2010 aime-bijou iniongo
** Last update Sat Jun 19 18:08:58 2010 aime-bijou iniongo
*/

#include "../includes/server.h"

void		ghost_mode(t_play *player, t_env *e)
{
  return_place_on_team(&player[e->i], e->team);
  close(player[e->i].cs);
  player[e->i].type = FD_GHOST;
  FD_CLR(player[e->i].cs, &e->readfs);
  FD_CLR(player[e->i].cs, &e->wrtefs);
}

void	temp_life(t_play *player, t_env *e, t_desc *serv, t_timev t)
{
  double time1;
  double time2;

  gettimeofday(&e->tv, NULL);
  time1 = (double)e->tv.tv_sec + (double)e->tv.tv_usec / 1000000;
  time2 = (double)t.t_old.tv_sec + (double)t.t_old.tv_usec / 1000000;
  if (serv->tv != NULL && t.d == 1)
    if (my_strcmp(t.action, "vie") == 0 && time1 >= time2)
      {
	if (player->inv[0] > 0)
	  {
	    player->inv[0]--;
	    e->end = 1;
	    e->state  = 0;
	    del_elem_to_queu(&serv->tv, t);
	    add_elem(&serv->tv, "vie", player->cs, e);
	  }
	else
	  {
	    player->type = FD_FREE;
	    if (player[e->i].team != NULL)
	      {
		return_place_on_team(&player[e->i], e->team);
		free(player[e->i].team);
		player[e->i].team = NULL;
	      }
	    printf("deleting client %d\n", player[e->i].cs);
	  }
      }
}

