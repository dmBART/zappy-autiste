/*
** do_server.c for do server in /u/all/iniong_a/cu/rendu/c/zappy/src_server
** 
** Made by aime-bijou iniongo
** Login   <iniong_a@epitech.net>
** 
** Started on  Wed May 26 14:14:09 2010 aime-bijou iniongo
<<<<<<< .mine
** Last update Sun Jun 20 23:12:38 2010 alexis milbault
=======
<<<<<<< .mine
** Last update Sun Jun 20 22:26:13 2010 alexandra ekra
=======
** Last update Sun Jun 20 22:46:37 2010 aime-bijou iniongo
>>>>>>> .r65
>>>>>>> .r64
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
      if (players[x].type == FD_CLIENT ||
	  players[x].type == FD_GRAPHIC)
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

void			manage_serveur(t_desc *serv, t_env *e)
{
  int			i;
  t_timev		t;
  struct timeval	tv;

  FD_ZERO(&e->readfs);
  FD_ZERO(&e->wrtefs);
  i = -1;
  FD_SET(serv->s, &e->readfs);
  t = manage_time(serv);
  while (++i < MAX_FD)
    if (serv->players[i].type != FD_FREE)
      {
	FD_SET(serv->players[i].cs, &e->readfs);
	FD_SET(serv->players[i].cs, &e->wrtefs);
      }
  e->fd_max = search_max_fd(serv->players, e->fd_max);
  manage_time_in_select(t, &tv);
  xselect(e->fd_max + 1, &e->readfs, &e->wrtefs, NULL, &tv);
  if (FD_ISSET(serv->s, &e->readfs))
    add_players(serv, e);
  manage_client(serv, e, t);
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

void		init_struct_player(t_play *players)
{
  int		i;

  i = -1;
  while (++i < MAX_GHOST)
    {
      players[i].type = FD_FREE;
      players[i].cs = 0;
    }

}

void			start_server(t_desc *serv)
{
  t_env			e;
  int			i;
  int			x;

  serv->s = init_serveur(serv);
  xlisten(serv->s, 42);
  i = 0;
  x = i;
  e.fd_max = serv->s;
  e.team = NULL;
  e.t = 0;
  e.graph_cs = -1;
  serv->tv = NULL;
  while (serv->team[x] != NULL)
    add_elem_in_team(serv, &e.team, x++);
  init_struct_player(serv->players);
/*   init_struct_player(serv->players, FD_GHOST, MAX_GHOST, MAX_FD + 1); */
  while (1)
    manage_serveur(serv, &e);
}
