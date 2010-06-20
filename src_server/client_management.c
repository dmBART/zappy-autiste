/*
** client_management.c for serveur in /u/all/iniong_a/cu/rendu/c/zappy/src_server
** 
** Made by aime-bijou iniongo
** Login   <iniong_a@epitech.net>
** 
** Started on  Fri May 28 00:49:11 2010 aime-bijou iniongo
** Last update Sun Jun 20 16:46:45 2010 alexandra ekra
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

void		ghost_mode(t_play *player, t_env *e)
{
  return_place_on_team(&player[e->i], e->team);
  close(player[e->i].cs);
  player[e->i].type = FD_GHOST;
  FD_CLR(player[e->i].cs, &e->readfs);
  FD_CLR(player[e->i].cs, &e->wrtefs);
}

void		close_client(t_play *player, t_env *e)
{
  player[e->i].type = FD_FREE;
  close(player[e->i].cs);
  if (player[e->i].team != NULL)
    {
      return_place_on_team(&player[e->i], e->team);
      free(player[e->i].team);
    }
  player[e->i].team = NULL;
  printf("client %d disconnected\n", player[e->i].cs);
  FD_CLR(player[e->i].cs, &e->readfs);
  FD_CLR(player[e->i].cs, &e->wrtefs);
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
      if (time1 >= time2)
	if (player->type == FD_CLIENT)
	  {
 	    t.d = 0;
	    if (my_strcmp(t.action, "vie") == 0)
	      {
		manage_life(player, e, serv, t);
	      }
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

void	first_read(t_play *players, t_env *e)
{
/*   if (players[e->i].inv[0] > 0) */
/*     { */
/*       ghost_mode(players, e); */
/*       printf("client in ghost mode\n"); */
/*     } */
/*   else */
/*     { */
      close_client(players, e);
      printf("deleting client %d\n", players[e->i].cs);
/*     } */
}

void	manage_client(t_desc *serv, t_env *e, t_timev t)
{
  int	n;
  char	buff[4091];

  e->i = -1;
  while (e->i++ < MAX_FD)
    {
      if (serv->players[e->i].type == FD_CLIENT &&
	  FD_ISSET(serv->players[e->i].cs, &e->readfs))
	{
	  n = xrecv(serv->players[e->i].cs, buff, 4090, 0);
	  if (n == 0)
	    first_read(serv->players, e);
	  else if (n > 0)
	    {
	      manage_buff(&serv->players[e->i], buff, n);
	      if (!my_strcmp(serv->players[e->i].action[serv->players[e->i].end - 1], "GRAPHIC"))
		{
		  serv->players[e->i].type = FD_GRAPHIC;
		  graphic_write(serv, serv->players, e);
		}
	      else
		{
 		  if ((serv->players[e->i].end % 100) == 0)
 		    serv->players[e->i].end++;
		  client_write(serv, e, n);
		}
	    }
	  memset(buff, 0, 4091);
	}
      if (serv->players[e->i].type == FD_CLIENT)
	{
	  if (serv->players[e->i].cs == t.cs && FD_ISSET(t.cs, &e->wrtefs))
	    treat_command(serv, e, &serv->players[e->i], t);
	}
      else if (serv->players[e->i].type == FD_GRAPHIC)
	read_graph(serv, serv->players, e);
      /*       else if (serv->players[e->i].type == FD_GHOST) */
      /*  	temp_life(&serv->players[e->i],  e, serv, t); */
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
