/*
** do_server.c for do server in /u/all/iniong_a/cu/rendu/c/zappy/src_server
** 
** Made by aime-bijou iniongo
** Login   <iniong_a@epitech.net>
** 
** Started on  Wed May 26 14:14:09 2010 aime-bijou iniongo
** Last update Sat May 29 22:11:28 2010 aime-bijou iniongo
*/

#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include "../includes/server.h"


int			manage_time(t_desc *serv, t_play *players)
{
  int			t;

  t = 0;
  return (t);
}

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

void			manage_serveur(t_desc *serv, t_env *e, t_play *players)
{
  int			t;
  int			i;
  fd_set		readfs;
  struct timeval	tv;

  t = manage_time(serv, players);
  tv.tv_sec = 0;
  tv.tv_usec = t;
  FD_ZERO(&readfs);
  i = 0;
  FD_SET(serv->s, &readfs);
  while (i < MAX_FD)
    {
      if (players[i].type != FD_FREE)
	FD_SET(players[i].cs, &readfs);
      i++;
    }
  e->fd_max = search_max_fd(players, e->fd_max);
  xselect(e->fd_max + 1, &readfs, NULL, NULL, &tv);
  if (FD_ISSET(serv->s, &readfs))
    add_players(serv->s, e, players);
  else
    manage_client(serv, players, readfs);
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
  t_play		players[MAX_FD];

  serv->s = init_serveur(serv);
  xlisten(serv->s, 42);
  i = 0;
  e.fd_max = serv->s;
  while (i < MAX_FD)
    {
      players[i].type = FD_FREE;
      players[i].cs = 0;
      i++;
    }
  while (1)
    manage_serveur(serv, &e, players);
}
