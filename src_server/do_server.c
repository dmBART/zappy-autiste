/*
** do_server.c for do server in /u/all/iniong_a/cu/rendu/c/zappy/src_server
** 
** Made by aime-bijou iniongo
** Login   <iniong_a@epitech.net>
** 
** Started on  Wed May 26 14:14:09 2010 aime-bijou iniongo
** Last update Fri Jun 11 03:17:47 2010 aime-bijou iniongo
*/

#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include "../includes/server.h"


int	search_max_fd(t_play *players, int fd_max)
{
  int	x;

  x = 0;
  while (x < MAX_FD)
    {
      if (players[x].type == FD_CLIENT)
	fd_max = MAX_NB(fd_max, players[x].cs);
      x++;
    }
  return (fd_max);
}

int	check_fd(t_play	*players)
{
  int	i;

  i = -1;
  while (i++ < MAX_FD)
    {
      if (players[i].type != FD_FREE)
	return (1);
    }
  return (0);
}

void			manage_serveur(t_desc *serv, t_env *e, t_play *players)
{
  int			i;
  t_timev		t;
  struct timeval	tv;

  FD_ZERO(&e->readfs);
  i = -1;
  FD_SET(serv->s, &e->readfs);
  t = manage_time(serv);
  while (++i < MAX_FD)
    if (players[i].type != FD_FREE)
      FD_SET(players[i].cs, &e->readfs);
  e->fd_max = search_max_fd(players, e->fd_max);
  manage_time_in_select(t, &tv);
  xselect(e->fd_max + 1, &e->readfs, NULL, NULL, &tv);
  if (FD_ISSET(serv->s, &e->readfs))
    add_players(serv->s, e, players);
  manage_client(serv, players, e, t);
   if (t.action != NULL)
     {
       t.action = NULL;
       t.t = 0;
     }
}

int			init_serveur(t_desc *serv)
{
  int			s;
  struct sockaddr_in	ser;

  s = xsocket(PF_INET, SOCK_STREAM, 0);
  ser.sin_family = AF_INET;
  ser.sin_port = htons(serv->port);
  ser.sin_addr.s_addr = INADDR_ANY;
  xbind(s, ser);
  return (s);
}

void			start_server(t_desc *serv)
{
  t_env			e;
  int			i;
  int			x;
  t_play		players[MAX_FD];

  serv->s = init_serveur(serv);
  xlisten(serv->s, 42);
  i = 0;
  x = i;
  e.fd_max = serv->s;
  e.team = NULL;
  e.t = 0;
  serv->tv = NULL;
  while (serv->team[x] != NULL)
    add_elem_in_team(serv, &e.team, x++);
  while (i < MAX_FD)
    {
      players[i].type = FD_FREE;
      players[i].cs = 0;
      i++;
    }
  while (1)
    manage_serveur(serv, &e, players);
}
