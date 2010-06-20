/*
** client_management.c for serveur in /u/all/iniong_a/cu/rendu/c/zappy/src_server
** 
** Made by aime-bijou iniongo
** Login   <iniong_a@epitech.net>
** 
** Started on  Fri May 28 00:49:11 2010 aime-bijou iniongo
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include "../includes/server.h"

void		my_putchar(char c)
{
  write(1, &c, 1);
}

void		close_client(t_timev *eve, t_play *player, t_env *e)
{
  int		x;
  int		size;

  x = 0;
  player->type = FD_FREE;
  size = count_elem_timer(eve, player->cs);
  close(player->cs);
  if (size > 0)
    del_elem_player(&eve, player->cs, size);
  if (player->team != NULL)
    {
      return_place_on_team(player, e->team);
      free(player->team);
    }
  free(player->inv);
  player->team = NULL;
  printf("client %d disconnected\n", player->cs);
  FD_CLR(player->cs, &e->readfs);
  FD_CLR(player->cs, &e->wrtefs);
}

void		init_ghost(t_play *ghost_player, t_play *player)
{
  int		i;

  i = -1;
  ghost_player->type = FD_GHOST;
  ghost_player->x = player->x;
  ghost_player->y = player->y;
  ghost_player->dir = player->x;
  ghost_player->lvl = player->lvl;
  ghost_player->state = player->state;
  ghost_player->end = player->end;
  ghost_player->cs = player->cs;
  printf("ghost = %d\n", ghost_player->cs);
  ghost_player->team = strdup(player->team);
  ghost_player->inv = xmalloc(sizeof(int *) * 7);
  while (i++ < 7)
    ghost_player->inv[i] = player->inv[i];
}


void		ghost_mode(t_timev *eve, t_play *player, t_env *e)
{
  int		size;
  int		i;

  size = count_elem_timer(eve, player->cs);
  i = MAX_FD + 1;
  while (i < MAX_GHOST)
    {
      if (player[e->i].type !=  FD_GHOST)
	{
	  printf("i in ta soeur = %d\n", i);
	  break;
	}
      i++;
    }
  init_ghost(&player[i], &player[e->i]);
  FD_CLR(player[e->i].cs, &e->readfs);
  FD_CLR(player[e->i].cs, &e->wrtefs);
  close(player[e->i].cs);
  player[e->i].type = FD_FREE;
  close_client(eve, &player[e->i], e);
}

void	treat_command(t_desc *serv, t_env *e, t_play *player, t_timev t)
{
  double time1;
  double time2;

  gettimeofday(&e->tv, NULL);
  if (serv->tv != NULL && t.d == 1)
    {
      time1 = (double)e->tv.tv_sec + (double)e->tv.tv_usec / 1000000;
      time2 = (double)t.t_old.tv_sec + (double)t.t_old.tv_usec / 1000000;
      if (time1 >= time2 && player->type == FD_CLIENT)
	{
 	    t.d = 0;
	    if (my_strcmp(t.action, "vie") == 0)
	      manage_life(player, e, serv, t);
 	    else
	      {
		my_putstr("executing commande \" ");
		my_putstr(t.action);
		my_putstr(" \" from player : ");
		my_putnbr_fd(1, t.cs);
		my_putstr("\n");
		manage_commande(serv, player, e, t.action);
		del_elem_to_queu(&serv->tv, t);
	      }
	  }
    }
}

void	first_read(t_timev *eve, t_play *players, t_env *e, int now)
{
      close_client(eve, &players[now],  e);
      printf("deleting client %d\n", players[now].cs);
}

void	treat_temp(t_desc *serv, t_env *e, int n, char *buff)
{
  if (n == 0)
    first_read(serv->tv, serv->players, e, e->i);
  else if (n > 0)
    {
      manage_buff(&serv->players[e->i], buff, n);
      if (!my_strcmp(serv->players[e->i].action, "GRAPHIC"))
	{
	  serv->players[e->i].type = FD_GRAPHIC;
	  e->graph_cs = serv->players[e->i].cs;
	  graphic_write(serv, serv->players, e);
	}
      else
	{
	  if ((serv->players[e->i].end % 100) == 0)
	    serv->players[e->i].end++;
	  client_write(serv, e, n);
	}
    }
}

void	manage_client(t_desc *serv, t_env *e, t_timev t)
{
  int	n;
  int	i;
  char	buff[4091];

  e->i = -1;
  i = MAX_FD;
  while (e->i++ < MAX_FD)
    {
      if ((serv->players[e->i].type == FD_CLIENT ||
	   serv->players[e->i].type == FD_GRAPHIC) &&
	  FD_ISSET(serv->players[e->i].cs, &e->readfs))
	{
	  n = xrecv(serv->players[e->i].cs, buff, 4090, 0);
	  treat_temp(serv, e, n, buff);
	  memset(buff, 0, 4091);
	}
      if (serv->players[e->i].type == FD_CLIENT)
 	{
	  if (serv->players[e->i].cs == t.cs && FD_ISSET(t.cs, &e->wrtefs))
	    treat_command(serv, e, &serv->players[e->i], t);
	}
      if (serv->players[e->i].type == FD_GRAPHIC &&
	  FD_ISSET(serv->players[e->i].cs, &e->readfs))
	graph_command(serv, serv->players, e);
    }
}

void			add_players(t_desc *serv, t_env *e)
{
  int			x;
  int			i;
  unsigned int		len;
  struct sockaddr_in	client;

  x = 0;
  i = 0;
  len = sizeof(client);
  if ((e->cs = accept(serv->s, (struct sockaddr*)&client, &len)) != -1)
    while (x < MAX_FD)
      {
	if (serv->players[x].type == FD_FREE)
	  {
	    init_client(&serv->players[x], e->cs, inet_ntoa(client.sin_addr), serv);
	    break;
	  }
	x++;
      }
}
